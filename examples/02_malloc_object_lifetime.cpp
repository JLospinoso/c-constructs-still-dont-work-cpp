#include <cstdlib>
#include <iostream>
#include <memory>
#include <new>
#include <string>
#include <type_traits>
#include <utility>

struct TrivialRecord {
  int a;
  int b;
};

struct NeedsConstructor {
  explicit NeedsConstructor(std::string value) : value(std::move(value)) {}
  std::string value;
};

int main() {
  static_assert(std::is_trivially_copyable_v<TrivialRecord>);

  // C++20: malloc can implicitly create objects of implicit-lifetime types
  // when doing so gives the program defined behavior. Values are still not
  // initialized until we assign them.
  auto* record = static_cast<TrivialRecord*>(std::malloc(sizeof(TrivialRecord)));
  if (!record) {
    return 1;
  }
  record->a = 1;
  record->b = 2;
  std::cout << record->a + record->b << '\n';
  std::free(record);

#if defined(DEMO_UNDEFINED_STRING_FROM_MALLOC)
  // Compiles, but it is undefined behavior if executed: no std::string object
  // was constructed in this storage.
  auto* bad = static_cast<std::string*>(std::malloc(sizeof(std::string)));
  *bad = "hello";
  std::free(bad);
#endif

  // Correct low-level construction when you really manage raw storage.
  void* storage = ::operator new(sizeof(NeedsConstructor));
  auto* object = new (storage) NeedsConstructor("constructed");
  std::cout << object->value << '\n';
  std::destroy_at(object);
  ::operator delete(storage);
}
