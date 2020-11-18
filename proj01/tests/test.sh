#!/usr/bin/env bats

### Basic test that the code is working and is in verification mode 
@test "verify that the code is working" {
	
	run ./tests [ "$status" -eq 0 ]
	[ "${lines[0]}" = "--> verification_mode = 1" ]
}

### Test that all configurations give the same output as their reference output files

