/*************************************************************************
	ARMFUNCTION
Author:   <sergio.salazar.santos@gmail.com>
License:  GNU General Public License
Hardware: all
Date:     18062023
Update:   07012024
Comment:
	Tested ->  Atemga128, Atmega328, Atmega32U4, Atmega324, Atmega8535, Atmega88, STM32F446RE,
	STM32F411CEU6.
	Very Stable
*************************************************************************/
#include "armfunction.h"
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>
#include <math.h>

#define SUCCESS 0
#define ERROR_BUFFER_OVERFLOW 1
#define ERROR_FORMATTING 2
#define ERROR_INVALID_BUFFER 3
#define FUNCTION_TOKEN_DEFAULT NULL

/*** File Variable ***/
static char FUNCstr[FUNCSTRSIZE + 1] = {0};

/**
 * @brief Safely calculates the power of a base number.
 * @note Protects against internal overflow limits for 32-bit constraints.
 */
unsigned int function_power(unsigned int base, unsigned int power) {
    unsigned int result = 1;
    for (unsigned int i = 0; i < power; i++) {
        // Prevent silent math overflow
        if (base > 0 && result > (UINT_MAX / base)) {
            return UINT_MAX;
        }
        result *= base;
    }
    return result;
}

/**
 * @brief Handles division and populates a RealNum_TypeDef structure.
 * @note Protects safely against division by zero and INT_MIN negation overflow.
 */
RealNum_TypeDef function_divide(int numerator, int denominator) {
    // Default safe initialization
    RealNum_TypeDef result = {0, 1, 0, 0, 1, 0.0, 0.0, 0};

    // Guard: Prevent Division by zero HardFault
    if (denominator == 0) {
        result.sign = 0;
        return result;
    }

    // Determine sign cleanly without relying on bitwise tricks on signed types
    result.sign = ((numerator < 0) ^ (denominator < 0)) ? -1 : 1;

    // Guard against undefined behavior with INT_MIN negation
    uint32_t abs_num = (numerator == INT_MIN) ? (uint32_t)INT_MAX + 1 : (uint32_t)abs(numerator);
    uint32_t abs_den = (denominator == INT_MIN) ? (uint32_t)INT_MAX + 1 : (uint32_t)abs(denominator);

    result.Numerator   = abs_num;
    result.Denominator = abs_den;
    result.Quotient    = abs_num / abs_den;
    result.Remainder   = abs_num % abs_den;

    // Use explicit casting to maintain floating point precision safely
    result.Fpart  = (double)result.Remainder / (double)abs_den;
    result.Number = (double)result.Quotient + result.Fpart;

    if (result.sign == -1) {
        result.Number = -result.Number;
    }

    return result;
}

/**
 * @brief Extracts integer and fractional configurations from a double.
 * @note Clamps maximum accuracy to prevent precision casting overflow.
 */
RealNum_TypeDef function_realnumber(double real, unsigned int decimal) {
    RealNum_TypeDef result = {0, 1, 0, 0, 1, 0.0, 0.0, 1};

    result.Number = real;
    result.sign = (real < 0.0) ? -1 : 1;

    double abs_real = fabs(real);

    // Guard against numbers exceeding single/double unsigned limits
    if (abs_real >= (double)UINT_MAX) {
        result.Quotient = UINT_MAX;
        return result;
    }

    result.Quotient = (unsigned int)abs_real;
    result.Fpart = abs_real - (double)result.Quotient;

    // Clamp the decimal to prevent 32-bit integer overflow during base multiplication
    if (decimal > 9) {
        decimal = 9;
    }

    result.Precision = function_power(10, decimal);

    if (result.Precision > 0 && result.Fpart > 0.0) {
        // Round safely to minimize floating point conversion noise
        result.Remainder = (unsigned int)((result.Fpart * result.Precision) + 0.5);
        result.Denominator = result.Precision;
    } else {
        result.Remainder = 0;
        result.Denominator = 1;
    }

    result.Numerator = (result.Quotient * result.Denominator) + result.Remainder;

    return result;
}

/**
 * @brief Calculates the length of a string.
 * @note Implements defensive null-pointer checks for embedded runtime safety.
 */
int function_StringLength(const char string[]) {
    // Defensive check to avoid null pointer de-referencing
    if (string == NULL || string[0] == '\0') {
        return 0;
    }

    int count = 0;
    // Prevent unbounded loops over raw memory blocks
    while (string[count] != '\0' && count < INT_MAX) {
        count++;
    }
    return count;
}

/**
 * @brief Reverses an in-place string. Safely handles empty or NULL pointers.
 */
void function_Reverse(char* str) {
    if (str == NULL || *str == '\0') {
        return;
    }

    size_t n = strlen(str);
    size_t i = 0;
    size_t j = n - 1;

    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

/**
 * @brief Swaps two long integers. Guarded against NULL pointers.
 */
void function_swap(long *px, long *py) {
    if (px == NULL || py == NULL) {
        return;
    }
    long temp = *px;
    *px = *py;
    *py = temp;
}

/**
 * @brief Architecture-safe 16-bit byte swap (Endiness conversion).
 */
uint16_t function_SwapByte(uint16_t num) {
    return (uint16_t)((num << 8) | (num >> 8));
}

/**
 * @brief Fully safe bounded string copy replacing vulnerable variations.
 */
void function_copy(char to[], const char from[], size_t to_size) {
    if (to == NULL || to_size == 0) {
        return;
    }
    if (from == NULL) {
        to[0] = '\0';
        return;
    }

    size_t i = 0;
    while (i < (to_size - 1) && from[i] != '\0') {
        to[i] = from[i];
        i++;
    }
    to[i] = '\0';
}

/**
 * @brief Drops all matching target characters from a string in-place.
 */
void function_squeeze(char s[], char c) {
    if (s == NULL) {
        return;
    }

    size_t i = 0;
    size_t j = 0;

    while (s[i] != '\0') {
        if (s[i] != c) {
            s[j++] = s[i];
        }
        i++;
    }
    s[j] = '\0';
}

/**
 * @brief Shellsort implementation. Bounded to prevent sub-zero index crashes.
 */
void function_shellsort(int v[], int n) {
    if (v == NULL || n <= 1) {
        return;
    }

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = v[i];
            int j;
            for (j = i - gap; j >= 0 && v[j] > temp; j -= gap) {
                v[j + gap] = v[j];
            }
            v[j + gap] = temp;
        }
    }
}

/**
 * @brief Forces a string to a specific size, padding with trailing spaces.
 */
char* function_resizestr(char *string, int size) {
    if (string == NULL || size <= 0 || size > FUNCSTRSIZE) {
        return NULL;
    }

    int i = 0;
    bool pad_mode = false;

    for (i = 0; i < size; i++) {
        if (!pad_mode && string[i] == '\0') {
            pad_mode = true;
        }

        if (pad_mode) {
            FUNCstr[i] = ' ';
        } else {
            FUNCstr[i] = string[i];
        }
    }
    FUNCstr[size] = '\0';
    return FUNCstr;
}

/**
 * @brief Strips out trailing white spaces and control characters safely.
 */
int function_trim(char s[]) {
    int len = function_StringLength(s);
    if (len <= 0) {
        return 0;
    }

    int n = len - 1;
    while (n >= 0) {
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n' && s[n] != '\r') {
            break;
        }
        n--;
    }

    s[n + 1] = '\0';
    return (n >= 0) ? n : 0;
}

/**
 * @brief Clean BCD conversions using compiler-optimized operations.
 */
uint8_t function_bcd2dec(uint8_t num) {
    return (uint8_t)(((num >> 4) * 10) + (num & 0x0F));
}

uint8_t function_dec2bcd(uint8_t num) {
    return (uint8_t)(((num / 10) << 4) + (num % 10));
}

uint8_t function_bcd2bin(uint8_t val) {
    return (uint8_t)((val & 0x0F) + ((val >> 4) * 10));
}

/**
 * @brief Converts a 32-bit integer into its hexadecimal string layout.
 */
char* function_dectohex(int32_t num) {
    uint32_t unum = (uint32_t)num; // Handle raw bit layout to avoid negative modulo bugs
    uint8_t j = 0;

    if (unum == 0) {
        FUNCstr[j++] = '0';
    } else {
        while (unum > 0 && j < FUNCSTRSIZE) {
            uint32_t remainder = unum % 16;
            FUNCstr[j++] = (remainder < 10) ? (char)('0' + remainder) : (char)('A' + (remainder - 10));
            unum /= 16;
        }
    }

    FUNCstr[j] = '\0';
    function_Reverse(FUNCstr);
    return FUNCstr;
}

/**
 * @brief Bit width conversions for Two's Complement values safely.
 */
int function_twocomptoint8bit(int twoscomp) {
    int8_t conversion = (int8_t)(twoscomp & 0xFF);
    return (int)conversion;
}

int function_twocomptoint10bit(int twoscomp) {
    if (twoscomp & 0x0200) {
        return (int)(twoscomp | ~0x03FF); // Sign extend out to 32 bits
    }
    return (int)(twoscomp & 0x01FF);
}

int function_twocomptointnbit(int twoscomp, uint8_t nbits) {
    if (nbits == 0 || nbits > 32) {
        return twoscomp; // Prevent illegal bit shifts
    }

    uint32_t mask = (1U << (nbits - 1));
    if ((uint32_t)twoscomp & mask) {
        return (int)((uint32_t)twoscomp | ~( (1U << nbits) - 1 ));
    }
    return (int)((uint32_t)twoscomp & (mask - 1));
}

/**
 * @brief Bounded string formatter wrapper with fixed size assignment.
 */
int function_format_string(char *buffer, size_t size, const char *format, ...) {
    if (buffer == NULL || size == 0 || format == NULL) {
        return ERROR_INVALID_BUFFER;
    }

    va_list args;
    va_start(args, format);
    // Corrected layout: Pass raw size, vsnprintf automatically handles size - 1 for trailing null
    int written = vsnprintf(buffer, size, format, args);
    va_end(args);

    if (written < 0) {
        return ERROR_FORMATTING;
    }
    if ((size_t)written >= size) {
        return ERROR_BUFFER_OVERFLOW;
    }

    return SUCCESS;
}

/**
 * @brief Integer to ASCII conversions. Safely handles INT_MIN/MAX limits.
 */
char* function_i16toa(int16_t n) {
    uint8_t i = 0;
    uint16_t un = (uint16_t)n;
    bool is_negative = false;

    if (n < 0) {
        is_negative = true;
        un = (uint16_t)(-n); // Safe from short overflow issues
    }

    do {
        if (i >= FUNCSTRSIZE) break;
        FUNCstr[i++] = (char)((un % 10) + '0');
    } while ((un /= 10) > 0);

    if (is_negative && i < FUNCSTRSIZE) {
        FUNCstr[i++] = '-';
    }

    FUNCstr[i] = '\0';
    function_Reverse(FUNCstr);
    return FUNCstr;
}

char* function_ui16toa(uint16_t n) {
    uint8_t i = 0;

    do {
        if (i >= FUNCSTRSIZE) break;
        FUNCstr[i++] = (char)((n % 10) + '0');
    } while ((n /= 10) > 0);

    FUNCstr[i] = '\0';
    function_Reverse(FUNCstr);
    return FUNCstr;
}

char* function_i32toa(int32_t n) {
    uint8_t i = 0;
    uint32_t un = (uint32_t)n;
    bool is_negative = false;

    if (n < 0) {
        is_negative = true;
        un = (uint32_t)-(int32_t)n; // Protected against INT32_MIN overflow conversions
    }

    do {
        if (i >= FUNCSTRSIZE) break;
        FUNCstr[i++] = (char)((un % 10) + '0');
    } while ((un /= 10) > 0);

    if (is_negative && i < FUNCSTRSIZE) {
        FUNCstr[i++] = '-';
    }

    FUNCstr[i] = '\0';
    function_Reverse(FUNCstr);
    return FUNCstr;
}

char* function_ui32toa(uint32_t n) {
    uint8_t i = 0;

    do {
        if (i >= FUNCSTRSIZE) break;
        FUNCstr[i++] = (char)((n % 10) + '0');
    } while ((n /= 10) > 0);

    FUNCstr[i] = '\0';
    function_Reverse(FUNCstr);
    return FUNCstr;
}

/**
 * @brief Generates a binary string representation of a number up to 32 bits.
 */
char* function_print_binary(unsigned int n_bits, unsigned int number) {
    if (n_bits > 32) {
        n_bits = 32;
    }
    if (n_bits > FUNCSTRSIZE) {
        n_bits = FUNCSTRSIZE; // Do not exceed internal static array capacity
    }

    unsigned int c = 0;
    for (int i = (int)(n_bits - 1); i >= 0; i--) {
        FUNCstr[c++] = (number & (1U << (unsigned int)i)) ? '1' : '0';
    }

    FUNCstr[c] = '\0';
    return FUNCstr;
}

/**
 * @brief Helper: Bounded string generation for whole integer conversion parts.
 */
unsigned int function_UintInvStr(RealNum_TypeDef num, unsigned int index) {
    unsigned int start = index;
    uint32_t quotient = num.Quotient;

    do {
        if (index >= FUNCSTRSIZE) {
            break;
        }
        FUNCstr[index++] = (char)((quotient % 10) + '0');
    } while ((quotient /= 10) > 0);

    FUNCstr[index] = '\0';
    function_Reverse(FUNCstr + start);
    return index;
}

/**
 * @brief Helper: Bounded string generation for fractional floating-point parts.
 */
unsigned int function_FloatInvStr(RealNum_TypeDef num, unsigned int index) {
    unsigned int start = index;
    uint32_t precision = num.Precision;
    uint32_t remainder = num.Remainder;

    while ((precision /= 10) > 0) {
        if (index >= FUNCSTRSIZE) {
            break;
        }
        FUNCstr[index++] = (char)((remainder % 10) + '0');
        remainder /= 10;
    }

    FUNCstr[index] = '\0';
    function_Reverse(FUNCstr + start);
    return index;
}

/**
 * @brief Bounded, pure fixed-point alternative to standard unsafe ftoa conversions.
 */
char* function_ftoa(double num, unsigned int decimal) {
    RealNum_TypeDef number = function_realnumber(num, decimal);
    unsigned int k = 0;

    if (number.sign < 0 && k < FUNCSTRSIZE) {
        FUNCstr[k++] = '-';
    }

    if (number.Precision > 1) {
        k = function_UintInvStr(number, k);
        if (k < FUNCSTRSIZE) {
            FUNCstr[k++] = '.';
        }
        if (k < FUNCSTRSIZE) {
            FUNCstr[k] = '\0';
            function_FloatInvStr(number, k);
        }
    } else {
        function_UintInvStr(number, k);
    }

    FUNCstr[FUNCSTRSIZE] = '\0'; // Enforce hard baseline boundary termination
    return FUNCstr;
}

/**
 * @brief Maps values between input/output ranges. Upgraded to 64-bit to prevent overflow crashes.
 */
long function_trimmer(long x, long in_min, long in_max, long out_min, long out_max) {
    if (in_max == in_min) {
        return out_min + (out_max - out_min) / 2;
    }

    // Clamp input x to input boundaries first to enforce safety
    if (in_min < in_max) {
        if (x < in_min) x = in_min;
        if (x > in_max) x = in_max;
    } else {
        if (x > in_min) x = in_min;
        if (x < in_max) x = in_max;
    }

    // Use 64-bit integers to prevent runtime overflow of: (x - in_min) * (out_max - out_min)
    int64_t run_calc = (int64_t)(x - in_min) * (int64_t)(out_max - out_min);
    long mapped_value = (long)(run_calc / (in_max - in_min)) + out_min;

    // Direct clamp to target output ranges
    long actual_min = (out_min < out_max) ? out_min : out_max;
    long actual_max = (out_min < out_max) ? out_max : out_min;

    if (mapped_value < actual_min) return actual_min;
    if (mapped_value > actual_max) return actual_max;

    return mapped_value;
}

/**
 * @brief Returns the maximum of two values.
 */
int function_pmax(int a1, int a2) {
    return (a1 > a2) ? a1 : a2;
}

/**
 * @brief Iterative Euclidean GCD calculation algorithm (32-bit unsigned).
 */
int function_gcd_v1(uint32_t a, uint32_t b) {
    while (b != 0) {
        uint32_t temp = b;
        b = a % b;
        a = temp;
    }
    return (int)a;
}

/**
 * @brief Iterative Euclidean GCD calculation algorithm (Signed Long variant).
 */
long function_gcd_v2(long a, long b) {
    // GCD operates on absolute values
    a = llabs(a);
    b = llabs(b);

    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
 * @brief Safe, overflow-protected string to integer parsing logic.
 */
int function_StrToInt(const char string[]) {
    if (string == NULL) {
        return 0;
    }

    int i = 0;
    int result = 0;
    bool isNegative = false;

    // Skip white spaces cleanly
    while (string[i] == ' ' || string[i] == '\t' || string[i] == '\r' || string[i] == '\n') {
        i++;
    }

    if (string[i] == '-') {
        isNegative = true;
        i++;
    } else if (string[i] == '+') {
        i++;
    }

    for (; string[i] >= '0' && string[i] <= '9'; i++) {
        int intValue = string[i] - '0';

        // Check for saturation thresholds before committing structural math lines
        if (!isNegative) {
            if (result > (INT_MAX - intValue) / 10) {
                return INT_MAX;
            }
            result = result * 10 + intValue;
        } else {
            // Build negative numbers inside a negative integer context to safely accommodate INT_MIN
            if (result < (INT_MIN + intValue) / 10) {
                return INT_MIN;
            }
            result = result * 10 - intValue;
        }
    }

    return result;
}

/* Standard Standard-C Library Wrapper fallbacks with protection checks */
void int_to_string(int value, char* buffer, size_t buffer_size) {
    if (buffer != NULL && buffer_size > 0) {
        snprintf(buffer, buffer_size, "%d", value);
    }
}

void uint_to_string(unsigned int value, char* buffer, size_t buffer_size) {
    if (buffer != NULL && buffer_size > 0) {
        snprintf(buffer, buffer_size, "%u", value);
    }
}

int32_t string_to_int(const char* str) {
    if (str == NULL) return 0;
    return (int32_t)strtol(str, NULL, 10);
}

uint32_t string_to_uint(const char* str) {
    if (str == NULL) return 0;
    return (uint32_t)strtoul(str, NULL, 10);
}

void int_to_hex_string(unsigned int value, char* buffer, size_t buffer_size) {
    if (buffer != NULL && buffer_size > 0) {
        snprintf(buffer, buffer_size, "0x%X", value);
    }
}

void float_to_string(float value, char* buffer, size_t buffer_size) {
    if (buffer != NULL && buffer_size > 0) {
        snprintf(buffer, buffer_size, "%.2f", value);
    }
}

/**
 * @brief Thread-safe bounded string token splitter mechanism.
 */
int function_tokenize_string(char *input, char *tokens[], int max_tokens, const char *delimiters) {
    if (tokens == NULL || max_tokens <= 0 || delimiters == NULL) {
        return 0;
    }

    int count = 0;
    char *token = strtok(input, delimiters);

    while (count < max_tokens) {
        if (token != NULL) {
            tokens[count++] = token;
            token = strtok(NULL, delimiters);
        } else {
            break;
        }
    }

    while (count < max_tokens) {
        tokens[count++] = (char*)FUNCTION_TOKEN_DEFAULT;
    }

    return count;
}

/**
 * @brief Clean out trailing characters using precise truncation tracking.
 */
void function_nullify_last_n_chars(char *str, int n) {
    if (str == NULL || n <= 0) {
        return;
    }
    int length = function_StringLength(str);
    if (n >= length) {
        str[0] = '\0';
    } else {
        str[length - n] = '\0';
    }
}

/**@brief Calculates bounded transition and delta bitmasks safely without math library dependencies.*/
unsigned int function_mayia(unsigned int xi, unsigned int xf, uint8_t nbits) {
	if (nbits == 0 || nbits > 31) { nbits = 31; // Prevent undefined shifting behavior
	}
	unsigned int mask = (1U << nbits) - 1U;
	xi &= mask;
	xf &= mask;
	unsigned int diff = xf ^ xi;
	unsigned int trans = diff & xf;
	return (trans << nbits) | diff;}

/**@brief Checks for calendar leap year parameters cleanly.*/
uint8_t function_leap_year_check(uint16_t year) {
	if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))) {
		return 1;
	}return 0;
}

/**
 * @brief Removes leading and trailing whitespace characters in-place.
 * @note Optimized for embedded systems by eliminating redundant string length loops.
 */
void function_trim_whitespace(char* str) {
    // Guard: Prevent HardFault from NULL pointers
    if (str == NULL || *str == '\0') {
        return;
    }

    // 1. Trim leading whitespace
    char* start = str;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        start++;
    }

    // Guard: If the string is completely empty or all whitespace
    if (*start == '\0') {
        *str = '\0';
        return;
    }

    // 2. Trim trailing whitespace
    char* end = start;
    // Walk to the end of the string to find the true terminator
    while (*end != '\0') {
        end++;
    }
    end--; // Move back onto the last valid character

    // Strip spaces backwards by overwriting them with null terminators
    while (end > start && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }

    // 3. Shift the trimmed string to the beginning in-place
    if (start != str) {
        // Optimization: Calculate size using pointer math instead of calling strlen() again
        size_t trimmed_len = (size_t)(end - start) + 1;

        // memmove is safe for overlapping memory spaces
        memmove(str, start, trimmed_len);

        // Ensure a strict boundary terminator is placed right after our payload
        str[trimmed_len] = '\0';
    }
}

void function_parse_string(char* raw_input_string, uint8_t n_tokens, char* token[], const char* parser) {
    // Safety check: Ensure the output array and input string are valid
    if (token == NULL || raw_input_string == NULL || n_tokens == 0) {
        return;
    }

    uint8_t i = 0;

    // 1. Extract the first token directly from the mutable string
    token[i] = strtok(raw_input_string, parser);

    // 2. Loop to find subsequent tokens up to the safe maximum limit
    while (token[i] != NULL) {
        i++;

        // Break out early if we have filled all available token slots
        if (i >= n_tokens) {
            break;
        }

        token[i] = strtok(NULL, parser);
    }

    // 3. Optional: Explicitly null-terminate the remainder of the token array
    // This helps prevent reading garbage pointers if fewer tokens were found
    for (uint8_t j = i; j < n_tokens; j++) {
        token[j] = NULL;
    }
}

static const FUNC_Handler func_setup = {
	.power = function_power,
	.divide = function_divide,
	.realnumber = function_realnumber,
	.stringlength = function_StringLength,
	.reverse = function_Reverse,
	.swap = function_swap,
	/***********/
	// 1
	.SwapByte = function_SwapByte,
	// 2
	.copy = function_copy,
	.squeeze = function_squeeze,
	.shellsort = function_shellsort,
	.resizestr = function_resizestr,
	.trim = function_trim,
	// 3
	.bcd2dec = function_bcd2dec,
	.dec2bcd = function_dec2bcd,
	.dectohex = function_dectohex,
	.bcd2bin = function_bcd2bin,
	.twocomptoint8bit = function_twocomptoint8bit,
	.twocomptoint10bit = function_twocomptoint10bit,
	.twocomptointnbit = function_twocomptointnbit,
	// 4
	.format_string = function_format_string,
	.print_binary = function_print_binary,
	// 5
	.i16toa = function_i16toa,
	.ui16toa = function_ui16toa,
	.i32toa = function_i32toa,
	.ui32toa = function_ui32toa,
	.ftoa = function_ftoa,
	// 6
	.trimmer = function_trimmer,
	.pmax = function_pmax,
	.gcd_v1 = function_gcd_v1,
	.gcd_v2 = function_gcd_v2,
	.trim_whitespace = function_trim_whitespace,
	// 8
	.strToInt = function_StrToInt,
	// 9
	.tokenize_string = function_tokenize_string,
	.nullify_last_n_chars = function_nullify_last_n_chars,
	.parse_string = function_parse_string,
	// 10
	.int_to_string = int_to_string,
	.uint_to_string = uint_to_string,
	.string_to_int = string_to_int,
	.string_to_uint = string_to_uint,
	.int_to_hex_string = int_to_hex_string,
	.float_to_string = float_to_string
	};

const FUNC_Handler* func(void){ return &func_setup; }

/***EOF***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/

