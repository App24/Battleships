#pragma once

// The different difficulties that the game can be played at
enum class Difficulty {
	Easy,
	Medium,
	Hard
};

// The string version of the difficulties, allows for easy printing to the console
static const char* difficultyString[] = { 
	"Easy", 
	"Medium", 
	"Hard" 
};