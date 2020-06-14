TEST_DIR := tests

test: export TESTS_DIR = $(TEST_DIR)
test:
	$(TEST_DIR)/tests.sh
