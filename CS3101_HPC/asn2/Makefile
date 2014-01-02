#!/bin/bash



all: bentley.cilk kadane.c
	g++ -o kadane kadane.c
	cilk++ -o bentley bentley.cilk



clean:
	@rm -rf bentley
	@rm -rf kadane
	@echo removing binary file
