#!/bin/bash








	echo "Testing for n = 2048"
	echo "Testing via method 1"
	/usr/bin/time ./multpoly 2048 1
	echo ""
	echo "Testing via method 2"
	/usr/bin/time ./multpoly 2048 2
	echo ""
	echo "Testing for n = 131072"
	echo "Testing via method 1"
	/usr/bin/time ./multpoly 131072 1
	echo ""
	echo "Testing via method 2"
	/usr/bin/time ./multpoly 131072 2





