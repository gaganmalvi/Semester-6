/**
 * @file terminal.h
 * @author Gagan Malvi <malvi@aospa.co>
 * @brief Terminal color schemes and other extras
 */

#ifndef TERMINAL_H
#define TERMINAL_H

// Terminal color schemes
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"

// Macros for printing in color
#define print_green(...) printf(GREEN __VA_ARGS__ RESET)
#define print_red(...) printf(RED __VA_ARGS__ RESET)
#define print_blue(...) printf(BLUE __VA_ARGS__ RESET)
#define print_yellow(...) printf(YELLOW __VA_ARGS__ RESET)
#define print_white(...) printf(WHITE __VA_ARGS__ RESET)

#endif
