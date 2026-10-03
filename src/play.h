// Copyright (c) 2024 Nathan Greenfield. All rights reserved
#pragma once

#include <iostream>
#include <string>

// Function: playPoker
// Purpose: Uses the input stream and output stream to 
// play poker. See the assignment write-up for more
// Input: Takes in an input and output stream to interact
// And a number to seed the random generator
// Returns: Nothing
void playPoker(std::istream& in, std::ostream& out, unsigned seed);

// Function: playPoker
// Purpose: Creates file streams from inputed file names
// Then calls the above function
// Input: Takes two file names for the input file and output file
// And a number to seed the random generator
// Returns: Nothing
void playPoker(const std::string& inFile, const std::string& outFile, unsigned seed);
