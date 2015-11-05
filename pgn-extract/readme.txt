pgn-extract:
A Portable Game Notation (PGN) Manipulator for Chess Games
Version 17-21 by David J. Barnes (@kentdjb)
https://www.cs.kent.ac.uk/people/staff/djb/pgn-extract/

Overview
The program is designed to make it easy to extract selected games from a PGN format data file based on a wide variety of criteria. The criteria include:

textual move sequences;

the position reached after a sequence of moves;

information in the tag fields;

fuzzy board position;

and material balance in the ending.

The program includes a semantic analyser which will report errors in game scores and it is also able to detect duplicate games found in its input files.

The range of input move formats accepted is fairly wide and includes recognition of lower-case piece letters for English and upper-case piece letters for Dutch and German. The output is normally in English Standard Algebraic Notation (SAN), but this can be varied.

Extracted games may be written out either including or excluding comments, NAGs, variations, move numbers, tags and/or results. Games may be given ECO classifications derived from the accompanying file eco.pgn, or a customised version provided by the user.

The program is designed to be relatively memory-friendly, so it does not retain a game's moves in memory once it has been processed.

Use the --help argument to the program to get the full lists of arguments.

New in version 17-21
These are the changes in version 17-21:

Fixed errors in the half-move clock on castling and pawn promotion.

Added --nofauxep to suppress the en-passant square from EPD output when the capture is not available.

Fixed off-by-one in move number output with -F when white-to-move.

Added -Wxlalg to include 'x' in long-algebraic output.

Fixed bug in game counting with -#.

Suppressed games with null moves (--) in the main line.