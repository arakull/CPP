// ZDES BIL GERMAN PENISS AMBASSODOR
#include <TXLib.h>

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

/*!
	\brief Library
	\author ZDA
	\version 1.0
	\date   August 2026 (Summer School)
	\warning This library was created for educational purposes only

    An ordinary Library
*/

/**
 * @mainpage Quadratic Equation Solver
 *
 * @section intro Introduction
 *
 * This program is designed to solve linear and quadratic equations
 * of the form:
 *
 *     ax^2 + bx + c = 0
 *
 * The program determines the number of roots and calculates
 * their values when they exist
 *
 * @section features Features
 *
 * - Solving quadratic equations
 * - Solving linear equations
 * - Detecting equations with no roots
 * - Detecting equations with one root
 * - Detecting equations with two roots
 * - Detecting equations with an infinite number of roots
 * - Checking the correctness of user input
 * - Comparing floating-point numbers using the EPS precision
 * - Displaying colored text in the console
 * - Displaying the equation and the solution using different colors
 * - Output of ASCII art from a document.txt
 *
 * @section structure Program Structure
 *
 * The program is divided into several functions:
 *
 * - @ref SolvingEquation — determines the type of equation
 * - @ref SolvingLine — solves linear equations
 * - @ref SolvingSquare — solves quadratic equations
 * - @ref CompFloat — compares floating-point numbers
 * - @ref InputValues — reads the equation coefficients
 * - @ref InputWithCommentColor — reads a floating-point value with a colored prompt
 * - @ref OutputValues — displays the solution
 * - @ref OutputEquationColor — displays the equation using a specified color
 * - @ref PrintfColor — displays a string using a specified color
 * - @ref PrintfColorOneArgument — displays a formatted value using a specified color
 * - @ref PrintASCII — displays an ASCII image from a text file
 *
 * @section precision Floating-Point Precision
 *
 * Floating-point numbers are compared using the EPS (epsilon) constant to reduce errors caused by floating-point precision
 *
 * @section console Console Output
 *
 * The TXLib library is used to change the color of text displayed in the console
 */

//----------------------------------------------------------------

/**
 * @name Console Colors
 *
 * Color attributes used to display text in different colorsin the console
 *
 * @{
 */

#define BlackColor        0x0
#define BlueColor         0x1
#define GreenColor        0x2
#define CyanColor         0x3
#define RedColor          0x4
#define MagentaColor      0x5
#define DarkYellowColor   0x7
#define LightGrayColor    0x8
#define DarkGrayColor     0x9
#define LightBlueColor    0xA
#define LightGreenColor   0xB
#define LightRedColor     0xC
#define LightMagentaColor 0xD
#define YellowColor       0xE
#define WhiteColor        0xF

/** @} */

//----------------------------------------------------------------

enum CompIndicators
    {
    e_AreMore  =  1,
    e_AreLess  = -1,
    e_AreEqual =  0
    };

enum RootNumber
    {
    e_ZeroRoot = 0,
    e_OneRoot  = 1,
    e_TwoRoot  = 2,
    e_ManyRoot = 3
    };

//----------------------------------------------------------------

RootNumber     SolvingEquation        (float       a,           float  b,           float  c,  float* x1_ptr,    float* x2_ptr);
RootNumber     SolvingSquare          (float       a,           float  b,           float  c,  float* x1_ptr,    float* x2_ptr);
void           OutputValues           (int         res,         float  x1,          float  x2, int    TextColor, int    AnswerColor);
void           OutputEquationColor    (const char* String,      float  a,           float  b,  float  c,         int    Color);
RootNumber     SolvingLine            (float       b,           float  c,           float* x1_ptr);
bool           InputWithCommentColor  (const char* String,      float* InputNumber, int    Color);
void           PrintfColorOneArgument (const char* String,      float  x,           int    Color);
bool           InputValues            (float*      a,           float* b,           float* c);
CompIndicators CompFloat              (float       FirstNumber, float  SecondNumber);
void           PrintfColor            (const char* String,      int    Color);
void           PrintASCII             (const char* FileName,    int    Color);


//----------------------------------------------------------------

const double EPS       = 1e-5;
const bool   IsANumber = true;

//----------------------------------------------------------------

int main (void)
{
    PrintASCII ("ascii-art.txt", LightRedColor);

    float a = 0, b = 0, c = 0;

    if (InputValues (&a, &b, &c) == false) return 0;

    OutputEquationColor("%fx^2 + %fx + %f = 0\n", a, b, c, LightMagentaColor);

    float x1_ptr = 0, x2_ptr = 0;
    int res = SolvingEquation (a, b, c, &x1_ptr, &x2_ptr);

    OutputValues (res, x1_ptr, x2_ptr, YellowColor, LightBlueColor);

    return 0;
}

//----------------------------------------------------------------

/**
 * @brief Determines the type of equation and calls the appropriate function to solve it
 *
 * @param [in]  a      Coefficient before x^2
 * @param [in]  b      Coefficient before x
 * @param [in]  c      Free coefficient
 * @param [out] x1_ptr Pointer to the first root
 * @param [out] x2_ptr Pointer to the second root
 *
 * @return Number of roots:
 *         e_ZeroRoot - no roots
 *         e_OneRoot  - one root
 *         e_TwoRoot  - two roots
 *         e_ManyRoot - infinite number of roots
 *
 *         The function code looks like this:
 * \code
 *   RootNumber SolvingEquation (float a, float b, float c, float* x1_ptr, float* x2_ptr)
 *   {
 *       assert (x1_ptr);
 *       assert (x2_ptr);
 *       assert (x1_ptr != x2_ptr);
 *
 *       if (CompFloat (a, 0) == e_AreEqual) return  SolvingLine   (b, c, x1_ptr);
 *       else                                return  SolvingSquare (a, b, c, x1_ptr, x2_ptr);
 *   }
 * \endcode
 *
 * @note If a is equal to zero, the equation is considered linear
 */

RootNumber SolvingEquation (float a, float b, float c, float* x1_ptr, float* x2_ptr)
    {
        assert (x1_ptr);
        assert (x2_ptr);
        assert (x1_ptr != x2_ptr);

        if (CompFloat (a, 0) == e_AreEqual) return  SolvingLine   (b, c, x1_ptr);
        else                                return  SolvingSquare (a, b, c, x1_ptr, x2_ptr);
    }

//----------------------------------------------------------------

/**
 * @brief Reads all equation coefficients from the user
 *
 * @param [out] a Pointer to the coefficient before x^2
 * @param [out] b Pointer to the coefficient before x
 * @param [out] c Pointer to the free coefficient
 *
 * @return true if all coefficients were successfully entered
 * @return false if an input error occurred

 *         The function code looks like this:
 * \code
           bool InputValues (float* a, float* b, float* c)
            {
                assert (a);
                assert (b);
                assert (c);

                if (InputWithCommentColor ("Enter the coefficient a before x^2\n", a, WhiteColor) == false)
                    {
                        PrintfColor ("Input Error\n", RedColor);
                        return false;
                    }

                if (InputWithCommentColor ("Enter the coefficient b before x\n",   b, BlueColor) ==  false)
                    {
                        PrintfColor ("Input Error\n", RedColor);
                        return false;
                    }

                if (InputWithCommentColor ("Enter the coefficient c\n",            c, RedColor) ==   false)
                    {
                        PrintfColor ("Input Error\n", RedColor);
                        return false;
                    }

                return true;
            }
 * \endcode
 *
 * @note Each input prompt is displayed using a specified console color
 */

bool InputValues (float* a, float* b, float* c)
    {
        assert (a);
        assert (b);
        assert (c);

        if (InputWithCommentColor ("Enter the coefficient a before x^2\n", a, WhiteColor) == false)
            {
                PrintfColor ("Input Error\n", RedColor);
                return false;
            }

        if (InputWithCommentColor ("Enter the coefficient b before x\n",   b, BlueColor) ==  false)
            {
                PrintfColor ("Input Error\n", RedColor);
                return false;
            }

        if (InputWithCommentColor ("Enter the coefficient c\n",            c, RedColor) ==   false)
            {
                PrintfColor ("Input Error\n", RedColor);
                return false;
            }

        return true;
    }

//----------------------------------------------------------------

/**
 * @brief Displays the result of solving the equation
 *
 * @param [in] res         Number of roots
 * @param [in] x1          First root
 * @param [in] x2          Second root
 * @param [in] TextColor   Color used to display descriptive text
 * @param [in] AnswerColor Color used to display the roots
 *
 *         The function code looks like this:
 * \code
           void OutputValues (int res, float x1, float x2, int TextColor, int AnswerColor)
            {
                switch(res)
                    {
                        case e_ZeroRoot: PrintfColor            ("There are no solutions\n",                           TextColor);
                                        break;

                        case e_OneRoot:  PrintfColor            ("The equation has a unique solution\n",               TextColor);
                                        PrintfColorOneArgument  ("x = %.3f\n",  x1,                                    AnswerColor);
                                        break;

                        case e_TwoRoot:  PrintfColorOneArgument ("x1 = %.3f\n", x1,                                    AnswerColor);
                                        PrintfColorOneArgument  ("x2 = %.3f\n", x2,                                    AnswerColor);
                                        break;

                        case e_ManyRoot: PrintfColor            ("The equation has an infinite number of solutions\n", TextColor);
                                        break;

                        default:         PrintfColor            ("Error\n",                                            TextColor);
                                        break;
                    }
            }
  * \endcode
  *
  * @note The output depends on the number of roots descriptive messages and numerical answers can have different colors
  */

void OutputValues (int res, float x1, float x2, int TextColor, int AnswerColor)
    {
        switch(res)
            {
                case e_ZeroRoot: PrintfColor            ("There are no solutions\n",                           TextColor);
                                 break;

                case e_OneRoot:  PrintfColor            ("The equation has a unique solution\n",               TextColor);
                                 PrintfColorOneArgument ("x = %.3f\n",  x1,                                    AnswerColor);
                                 break;

                case e_TwoRoot:  PrintfColorOneArgument ("x1 = %.3f\n", x1,                                    AnswerColor);
                                 PrintfColorOneArgument ("x2 = %.3f\n", x2,                                    AnswerColor);
                                 break;

                case e_ManyRoot: PrintfColor            ("The equation has an infinite number of solutions\n", TextColor);
                                 break;

                default:         PrintfColor            ("Error\n",                                            TextColor);
                                 break;
            }
    }

//----------------------------------------------------------------

/**
 * @brief Solves a linear equation bx + c = 0
 *
 * @param [in]  b      Coefficient before x
 * @param [in]  c      Free coefficient
 * @param [out] x1_ptr Pointer to the root
 *
 * @return Number of roots:
 *         e_ZeroRoot - no roots
 *         e_OneRoot  - one root
 *         e_ManyRoot - infinite number of roots
 *
 *         The function code looks like this:
 * \code
           RootNumber SolvingLine (float b, float c, float* x1_ptr)
            {
                assert (x1_ptr);

                if (CompFloat (b, 0) == e_AreEqual)
                    {
                        if (CompFloat (c, 0) == e_AreEqual) return e_ManyRoot;
                        else                                return e_ZeroRoot;
                    }
                else
                    {
                        *x1_ptr = (-c) / (b);

                        return e_OneRoot;
                    }

            }
 * \endcode
 *
 * @note If b and c are both equal to zero, the equation has an infinite number of roots
 */

RootNumber SolvingLine (float b, float c, float* x1_ptr)
    {
        assert (x1_ptr);

        if (CompFloat (b, 0) == e_AreEqual)
            {
                if (CompFloat (c, 0) == e_AreEqual) return e_ManyRoot;
                else                                return e_ZeroRoot;
            }
        else
            {
                *x1_ptr = (-c) / (b);

                return e_OneRoot;
            }

    }

//----------------------------------------------------------------

/**
 * @brief Solves a quadratic equation ax^2 + bx + c = 0
 *
 * @param [in]  a      Coefficient before x^2
 * @param [in]  b      Coefficient before x
 * @param [in]  c      Free coefficient
 * @param [out] x1_ptr Pointer to the first root
 * @param [out] x2_ptr Pointer to the second root
 *
 * @return Number of roots:
 *         e_ZeroRoot - no roots
 *         e_OneRoot  - one root
 *         e_TwoRoot  - two roots
 *
 *         The function code looks like this:
 * \code
           RootNumber SolvingSquare (float a, float b, float c, float* x1_ptr, float* x2_ptr)
            {
                assert (x1_ptr);
                assert (x2_ptr);
                assert (x1_ptr != x2_ptr);

                float discriminant = b * b - 4 * a * c;

                if (CompFloat (0, discriminant) == e_AreMore) return e_ZeroRoot;
                else
                    {
                        float discriminantsq = sqrt(discriminant);

                        if (CompFloat (discriminant, 0) == e_AreEqual)
                            {
                                *x1_ptr = *x2_ptr = (-b) / (2 * a);

                                return e_OneRoot;
                            }
                        else
                            {
                                *x1_ptr = (-b + discriminantsq) / (2 * a);
                                *x2_ptr = (-b - discriminantsq) / (2 * a);

                                return e_TwoRoot;
                            }
                    }
            }
 * \endcode
 *
 * @note The discriminant is used to determine the number of roots floating-point values are compared using the EPS precision
 */

RootNumber SolvingSquare (float a, float b, float c, float* x1_ptr, float* x2_ptr)
    {
        assert (x1_ptr);
        assert (x2_ptr);
        assert (x1_ptr != x2_ptr);

        float discriminant = b * b - 4 * a * c;

        if (CompFloat (0, discriminant) == e_AreMore) return e_ZeroRoot;
        else
            {
                float discriminantsq = sqrt(discriminant);

                if (CompFloat (discriminant, 0) == e_AreEqual)
                    {
                        *x1_ptr = *x2_ptr = (-b) / (2 * a);

                        return e_OneRoot;
                    }
                else
                    {
                        *x1_ptr = (-b + discriminantsq) / (2 * a);
                        *x2_ptr = (-b - discriminantsq) / (2 * a);

                        return e_TwoRoot;
                    }
            }
    }

//----------------------------------------------------------------

/**
 * @brief Reads a floating-point value with a colored text prompt
 *
 * @param [in]  String      Text displayed before reading the value
 * @param [out] InputNumber Pointer to the variable where the value is stored
 * @param [in]  Color       Console color used to display the prompt
 *
 * @return true if a floating-point value was successfully read
 * @return false if the input was invalid
 *
 *         The function code looks like this:
 * \code
           bool InputWithCommentColor (const char* String, float* InputNumber, int Color)
            {
                assert (String);
                assert (InputNumber);

                PrintfColor (String,Color);

                if (scanf ("%f", InputNumber) == IsANumber) return true;
                else                                        return false;
            }
 * \endcode
 *
 * @note The specified color is applied only to the input prompt, the console color is restored after the prompt is displayed
 */

bool InputWithCommentColor (const char* String, float* InputNumber, int Color)
    {
        assert (String);
        assert (InputNumber);

        PrintfColor (String,Color);

        if (scanf ("%f", InputNumber) == IsANumber) return true;
        else                                        return false;
    }

//----------------------------------------------------------------

/**
 * @brief Compares two floating-point numbers with EPS precision
 *
 * @param [in] FirstNumber  First floating-point number
 * @param [in] SecondNumber Second floating-point number
 *
 * @return e_AreMore  if FirstNumber is greater than SecondNumber
 * @return e_AreLess  if FirstNumber is less than SecondNumber
 * @return e_AreEqual if the numbers are equal within EPS precision
 *
 *         The function code looks like this:
 * \code
           CompIndicators CompFloat (float FirstNumber, float SecondNumber)
            {
                if (fabs (FirstNumber - SecondNumber) < EPS) return e_AreEqual;
                else if (FirstNumber + EPS < SecondNumber)   return e_AreLess;
                else                                         return e_AreMore;
            }
 * \endcode
 *
 * @note The EPS (epsilon) value was calculated based on the selected float data type, if desired, you can change it in the constants section
 */

CompIndicators CompFloat (float FirstNumber, float SecondNumber)
    {
        if (fabs (FirstNumber - SecondNumber) < EPS) return e_AreEqual;
        else if (FirstNumber + EPS < SecondNumber)   return e_AreLess;
        else                                         return e_AreMore;
    }

//----------------------------------------------------------------

/**
 * @brief Displays a formatted equation using the specified console color
 *
 * @param [in] String Format string used to display the equation
 * @param [in] a      Coefficient before x^2
 * @param [in] b      Coefficient before x
 * @param [in] c      Free coefficient
 * @param [in] Color  Console color used to display the equation
 *
 *         The function code looks like this:
 * \code
           void OutputEquationColor (const char* String, float a, float b, float c, int Color)
            {
                assert (String);

                txSetConsoleAttr (Color);
                printf (String, a, b, c);
                txSetConsoleAttr (0x8);
            }
 * \endcode
 *
 * @note The console color is restored after the equation is displayed
 */

void OutputEquationColor (const char* String, float a, float b, float c, int Color)
    {
        assert (String);

        txSetConsoleAttr (Color);
        printf (String, a, b, c);
        txSetConsoleAttr (0x8);
    }

//----------------------------------------------------------------

/**
 * @brief Displays a string using the specified console color
 *
 * @param [in] String Text to display
 * @param [in] Color  Console color used to display the text
 *
 *         The function code looks like this:
 * \code
           void PrintfColor (const char* String, int Color)
            {
                assert (String);

                txSetConsoleAttr (Color);
                printf (String);
                txSetConsoleAttr (LightGrayColor);
            }
 * \endcode
 *
 * @note The console color is restored after the text is displayed
 */

void PrintfColor (const char* String, int Color)
    {
        assert (String);

        txSetConsoleAttr (Color);
        printf (String);
        txSetConsoleAttr (LightGrayColor);
    }

//----------------------------------------------------------------

/**
 * @brief Displays a formatted floating-point value using the specified console color
 *
 * @param [in] String Format string used to display the value
 * @param [in] x      Floating-point value to display
 * @param [in] Color  Console color used to display the value
 *
 *                    The function code looks like this:
 * \code
           void PrintfColorOneArgument (const char* String, float x, int Color)
            {
                txSetConsoleAttr (Color);
                printf (String, x);
                txSetConsoleAttr (LightGrayColor);
            }

 * \endcode
 * @note The console color is restored after the value is displayed
 */

void PrintfColorOneArgument (const char* String, float x, int Color)
    {
        assert (String);

        txSetConsoleAttr (Color);
        printf (String, x);
        txSetConsoleAttr (LightGrayColor);
    }

//----------------------------------------------------------------

/**
 * @brief Displays an ASCII image from a text file in the console
 *
 * @param [in] FileName Name of the text file containing the ASCII image
 * @param [in] Color    Console color used to display the ASCII image
 *                      The function code looks like this:
 * \code
           void PrintASCII (const char* FileName, int Color)
            {
                assert(FileName);

                FILE* File = fopen (FileName, "r");


                txSetConsoleAttr (Color);

                char String[256] = {};

                while (fgets (String, sizeof (String), File) != NULL)
                    {
                        printf ("%s", String);
                    }

                txSetConsoleAttr (LightGrayColor);

                fclose (File);
            }
 * \endcode
 *
 * @note The function reads the file line by line and displays its contents
 *       using the specified console color
 *
 * @note The console color is restored after the image is displayed
 */

void PrintASCII (const char* FileName, int Color)
    {
        assert(FileName);

        FILE* File = fopen (FileName, "r");


        txSetConsoleAttr (Color);

        char String[256] = {};

        while (fgets (String, sizeof (String), File) != NULL)
            {
                printf ("%s", String);
            }

        txSetConsoleAttr (LightGrayColor);

        fclose (File);
    }
