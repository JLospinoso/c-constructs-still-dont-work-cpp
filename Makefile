.PHONY: check clean

check:
	./scripts/check.sh

clean:
	rm -rf build .build
