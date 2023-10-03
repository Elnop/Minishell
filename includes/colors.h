/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperroti <lperroti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 05:49:06 by lperroti          #+#    #+#             */
/*   Updated: 2023/09/28 12:54:02 by lperroti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H
// =========================
//     PRINT WITH COLORS
// =========================
# define COLOR_OFF "\001\033[0m\002"       // Text Reset
// Regular Colors
# define BLACK "\001\033[0;30m\002"
# define RED "\001\033[0;31m\002"    
# define GREEN "\001\033[0;32m\002"        
# define YELLOW "\001\033[0;33m\002"       
# define BLUE "\001\033[0;34m\002"         
# define PURPLE "\001\033[0;35m\002"       
# define CYAN "\001\033[0;36m\002"         
# define WHITE "\001\033[0;37m\002"        
// Bold
# define BBLACK "\001\033[1;30m\002"       // BLACK
# define BRED "\001\033[1;31m\002"         // RED
# define BGREEN "\001\033[1;32m\002"       // GREEN
# define BYELLOW "\001\033[1;33m\002"      // YELLOW
# define BBLUE "\001\033[1;34m\002"        // BLUE
# define BPURPLE "\001\033[1;35m\002"      // PURPLE
# define BCYAN "\001\033[1;36m\002"        // CYAN
# define BWHITE "\001\033[1;37m\002"       // WHITE
// Underline
# define UBLACK "\001\033[4;30m\002"       // BLACK
# define URED "\001\033[4;31m\002"         // RED
# define UGREEN "\001\033[4;32m\002"       // GREEN
# define UYELLOW "\001\033[4;33m\002"      // YELLOW
# define UBLUE "\001\033[4;34m\002"        // BLUE
# define UPURPLE "\001\033[4;35m\002"      // PURPLE
# define UCYAN "\001\033[4;36m\002"        // CYAN
# define UWHITE "\001\033[4;37m\002"       // WHITE
// Background
# define BG_BLACK "\001\033[40m\002"       // BLACK
# define BG_RED "\001\033[41m\002"         // RED
# define BG_GREEN "\001\033[42m\002"       // GREEN
# define BG_YELLOW "\001\033[43m\002"      // YELLOW
# define BG_BLUE "\001\033[44m\002"        // BLUE
# define BG_PURPLE "\001\033[45m\002"      // PURPLE
# define BG_CYAN "\001\033[46m\002"        // CYAN
# define BG_WHITE "\001\033[47m\002"       // WHITE
// High Intensity
# define IBLACK "\001\033[0;90m\002"       // BLACK
# define IRED "\001\033[0;91m\002"         // RED
# define IGREEN "\001\033[0;92m\002"       // GREEN
# define IYELLOW "\001\033[0;93m\002"      // YELLOW
# define IBLUE "\001\033[0;94m\002"        // BLUE
# define IPURPLE "\001\033[0;95m\002"      // PURPLE
# define ICYAN "\001\033[0;96m\002"        // CYAN
# define IWHITE "\001\033[0;97m\002"       // WHITE
// Bold High Intensity
# define BIBLACK "\001\033[1;90m\002"      // BLACK
# define BIRED "\001\033[1;91m\002"        // RED
# define BIGREEN "\001\033[1;92m\002"      // GREEN
# define BIYELLOW "\001\033[1;93m\002"     // YELLOW
# define BIBLUE "\001\033[1;94m\002"       // BLUE
# define BIPURPLE "\001\033[1;95m\002"     // PURPLE
# define BICYAN "\001\033[1;96m\002"       // CYAN
# define BIWHITE "\001\033[1;97m\002"      // WHITE
// High Intensity backgrounds
# define BG_IBLACK "\001\033[0;100m\002"   // BLACK
# define BG_IRED "\001\033[0;101m\002"     // Red
# define BG_IGREEN "\001\033[0;102m\002"   // Green
# define BG_IYELLOW "\001\033[0;103m\002"  // YELLOW
# define BG_IBLUE "\001\033[0;104m\002"    // Blue
# define BG_IPURPLE "\001\033[0;105m\002"  // PURPLE
# define BG_ICYAN "\001\033[0;106m\002"    // Cyan
# define BG_IWHITE "\001\033[0;107m\002"   // White

#endif