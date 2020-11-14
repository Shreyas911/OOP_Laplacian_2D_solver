#!/usr/bin/env bats

@test "addition using bc" {
	result="$(echo 2+2 | bc)"
	[ "$result" -eq 4 ]
}

@test "verify that the code is working" {
	
	run ./tests [ "$status" -eq 0 ]
	[ "${lines[0]}" = "--> verification_mode = 1" ]
}
