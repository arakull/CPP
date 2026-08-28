// ZDES BIL GERMAN PENISS AMBASSODOR
#include <TXLib.h>

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

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
 * - Checking the user's login and password
 * - Registering new users
 * - Checking whether a username already exists
 * - Hashing passwords using the FNV-1a algorithm
 * - Reading and writing user data to a file
 * - Displaying the ASCII image of the authorized user
 * - Testing the equation solver using predefined test cases
 * - Checking the number and values of calculated roots
 * - Displaying information about failed tests
 *
 * @section structure Program Structure
 *
 * The program is divided into several functions:
 *
 * - @ref SolvEquation - determines the type of equation
 * - @ref SolvLine - solves linear equations
 * - @ref SolvSquare - solves quadratic equations
 * - @ref CompFloat - compares floating-point numbers
 * - @ref InputValues - reads the equation coefficients
 * - @ref InputWithCommentColor - reads a floating-point value with a colored prompt
 * - @ref PrintValues - displays the solution
 * - @ref PrintfColorTreeArgument - displays the equation using a specified color
 * - @ref PrintfColor - displays a string using a specified color
 * - @ref PrintASCII - displays an ASCII image from a text file
 * - @ref RunOneTest - runs and checks one test case
 * - @ref RunAllTest - runs all predefined test cases
 * - @ref PrintTestFailOneRoot - displays information about a failed one-root test
 * - @ref PrintTestFailTwoRoot - displays information about a failed two-root test
 * - @ref fnv32_hash - calculates the FNV-1a hash of a string
 * - @ref CheckLoginPassword - checks the user's login and password and displays the user's ASCII image
 * - @ref IsLoginExists - checks whether a username already exists in the user database
 * - @ref Registration - registers a new user and saves their data to the user database
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

struct TestSquare
    {
        float a, b, c;
        int   RootsRef;
        float x1Ref, x2Ref;
    };

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

void           PrintValues           (RootNumber  NumberRoots, float       x1,           float       x2, int    TextColor, int    AnswerColor);
RootNumber     SolvEquation          (float       a,           float       b,            float       c,  float* x1_ptr,    float* x2_ptr);
RootNumber     SolvSquare            (float       a,           float       b,            float       c,  float* x1_ptr,    float* x2_ptr);
void           PrintfColorArgument   (const char* String,      float       a,            float       b,  float  c,         int    Color);
void           PrintTestFailTwoRoot  (TestSquare  test,        float       x1,           float       x2, int    Roots);
RootNumber     SolvLine              (float       b,           float       c,            float*      x1_ptr);
bool           InputWithColorComment (const char* String,      float*      InputNumber,  int         Color);
bool           InputValues           (float*      a,           float*      b,            float*      c);
bool           CheckLoginPassword    (int         TextColor,   int         PictureColor, const char* FileName);
CompIndicators CompFloat             (float       FirstNumber, float       SecondNumber);
bool           Registration          (int         TextColor,   const char* FileName);
bool           IsLoginExists         (const char* Login,       const char* FileName);
uint32_t       fnv32_hash            (const char *str,         size_t      len);
void           PrintfColor           (const char* String,      int         Color);
bool           PrintASCII            (const char* FileName,    int         Color);
void           PrintTestFailOneRoot  (TestSquare  test,        float       x1Ref);
bool           RunOneTest            (TestSquare  test);
int            RunAllTest            (void);

//----------------------------------------------------------------

const double EPS         = 1e-5;
const bool   IsANumber   = true;
const int    LEN         = 256;
const bool   TestPassed  = false;
const bool   TestFailed  = true;
const bool   Right       = true;
const bool   Incorrect   = false;
const int    MaxLenLogin = 50;
const int    MaxLenPassword = 50;
const int    MaxPhotoFileName = 100;
const int    MaxLenAnswer = 50;

//----------------------------------------------------------------

int main (void)
{
    CheckLoginPassword (YellowColor, GreenColor, "users.txt");

    RunAllTest ();

    float a = 0, b = 0, c = 0;

    if (InputValues (&a, &b, &c) == false) return 0;

    PrintfColorArgument("%fx^2 + %fx + %f = 0\n", a, b, c, LightMagentaColor);

    float x1_ptr = 0, x2_ptr = 0;
    RootNumber NumberRoots  = SolvEquation  (a, b, c, &x1_ptr, &x2_ptr);

    PrintValues (NumberRoots, x1_ptr, x2_ptr, YellowColor, LightBlueColor);

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
 * @note If a is equal to zero, the equation is considered linear
 */

RootNumber SolvEquation  (float a, float b, float c, float* x1_ptr, float* x2_ptr)
    {
        assert (x1_ptr);
        assert (x2_ptr);
        assert (x1_ptr != x2_ptr);

        if (CompFloat (a, 0) == e_AreEqual) return  SolvLine   (b, c, x1_ptr);
        else                                return  SolvSquare (a, b, c, x1_ptr, x2_ptr);
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
 *
 * @note Each input prompt is displayed using a specified console color
 */

bool InputValues (float* a, float* b, float* c)
    {
        assert (a);
        assert (b);
        assert (c);

        if (InputWithColorComment ("Enter the coefficient a before x^2\n", a, WhiteColor) == false)
            {
                PrintfColor ("Input Error\n", RedColor);
                return false;
            }

        if (InputWithColorComment ("Enter the coefficient b before x\n",   b, BlueColor) ==  false)
            {
                PrintfColor ("Input Error\n", RedColor);
                return false;
            }

        if (InputWithColorComment ("Enter the coefficient c\n",            c, RedColor) ==   false)
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
 * @param [in] NumberRoots Number of roots
 * @param [in] x1          First root
 * @param [in] x2          Second root
 * @param [in] TextColor   Color used to display descriptive text
 * @param [in] AnswerColor Color used to display the roots
 *
 * @note The output depends on the number of roots descriptive messages and numerical answers can have different colors
 */

void PrintValues (RootNumber NumberRoots , float x1, float x2, int TextColor, int AnswerColor)
    {
        switch(NumberRoots )
            {
                case e_ZeroRoot: PrintfColor         ("There are no solutions\n",                           TextColor);
                                 break;

                case e_OneRoot:  PrintfColor         ("The equation has a unique solution\n",               TextColor);
                                 PrintfColorArgument ("x = %.3f\n",  x1, 0, 0,                              AnswerColor);
                                 break;

                case e_TwoRoot:  PrintfColorArgument ("x1 = %.3f\n", x1, 0,   0,                            AnswerColor);
                                 PrintfColorArgument ("x2 = %.3f\n", x2, 0,   0,                            AnswerColor);
                                 break;

                case e_ManyRoot: PrintfColor         ("The equation has an infinite number of solutions\n", TextColor);
                                 break;

                default:         PrintfColor         ("Error\n",                                            TextColor);
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
 * @note If b and c are both equal to zero, the equation has an infinite number of roots
 */

RootNumber SolvLine (float b, float c, float* x1_ptr)
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
 * @note The discriminant is used to determine the number of roots floating-point values are compared using the EPS precision
 */

RootNumber SolvSquare (float a, float b, float c, float* x1_ptr, float* x2_ptr)
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
                        *x1_ptr = (-b) / (2 * a);

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
 * @note The specified color is applied only to the input prompt, the console color is restored after the prompt is displayed
 */

bool InputWithColorComment (const char* String, float* InputNumber, int Color)
    {
        assert (String);
        assert (InputNumber);

        PrintfColor (String,Color);

        return (scanf ("%f", InputNumber) == IsANumber);
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
 * @note The EPS (epsilon) value was calculated based on the selected float data type, if desired, you can change it in the constants section
 */

CompIndicators CompFloat (float FirstNumber, float SecondNumber)
    {
        if      (fabs (FirstNumber - SecondNumber) < EPS) return e_AreEqual;
        else if (FirstNumber + EPS < SecondNumber)        return e_AreLess;
        else                                              return e_AreMore;
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
 * @note The console color is restored after the equation is displayed
 */

void PrintfColorArgument (const char* String, float a, float b, float c, int Color)
    {
        assert (String);

        txSetConsoleAttr (Color);
        printf (String, a, b, c);
        txSetConsoleAttr (LightGrayColor);
    }

//----------------------------------------------------------------

/**
 * @brief Displays a string using the specified console color
 *
 * @param [in] String Text to display
 * @param [in] Color  Console color used to display the text
 *
 * @note The console color is restored after the text is displayed
 */

void PrintfColor (const char* String, int Color)
    {
        assert (String);

        txSetConsoleAttr (Color);
        printf ("%s\n",String);
        txSetConsoleAttr (LightGrayColor);
    }


//----------------------------------------------------------------

/**
 * @brief Displays an ASCII image from a text file in the console
 *
 * @param [in] FileName Name of the text file containing the ASCII image
 * @param [in] Color    Console color used to display the ASCII image
 *
 * @note The function reads the file line by line and displays its contents
 *       using the specified console color
 *
 * @note The console color is restored after the image is displayed
 */

bool PrintASCII (const char* FileName, int Color)
    {
        assert(FileName);

        FILE* File = fopen (FileName, "r");

        if (File == NULL)
            {
                PrintfColor("Input Error File\n", RedColor);
                return false;
            }

        txSetConsoleAttr (Color);

        char String[LEN] = {};

        while (fgets (String, sizeof (String), File) != NULL)
            {
                printf ("%s", String);
            }

        txSetConsoleAttr (LightGrayColor);

        fclose (File);

        return true;
    }

//----------------------------------------------------------------

/**
 * @brief Displays information about a failed test with one expected root
 *
 * @param [in] test Test case containing the expected root
 * @param [in] x1 First root received from the equation solver
 *
 * @note The function displays the expected and received values of the root
 */

bool RunOneTest (TestSquare  test)
    {
        float x1 = 0, x2 = 0;
        RootNumber Roots = SolvEquation  (test.a, test.b, test.c, &x1, &x2);

        PrintfColorArgument("%fx^2 + %fx + %f = 0\n", test.a, test.b, test.c,LightMagentaColor);
        if (Roots != test.RootsRef)
            {
                PrintfColor ("During the test, the number of roots did not match\n", RedColor);
                return TestFailed;
            }
        else if ((CompFloat(x1, test.x1Ref) != e_AreEqual) || (CompFloat(x2, test.x2Ref) != e_AreEqual) )
            {
                switch(Roots)
                    {
                        case e_ZeroRoot:    PrintfColor ("Test Fail: The root of the equation is incorrect\n", RedColor);
                                            return TestFailed;
                                            break;

                        case e_OneRoot:     if ((CompFloat(x1, test.x1Ref) != e_AreEqual))
                                                {
                                                    PrintTestFailOneRoot (test, x1);
                                                    return TestFailed;
                                                }
                                            break;

                        case e_TwoRoot:     PrintTestFailTwoRoot (test, x1, x2, Roots);
                                            return TestFailed;
                                            break;

                        case e_ManyRoot:    PrintfColor ("Error\n", RedColor);
                                            return TestFailed;
                                            break;

                        default:            PrintfColor ("Error\n", RedColor);
                                            return TestFailed;
                                            break;
                    }
            }


        PrintfColor ("APPROVED\n", GreenColor);

        return TestPassed;
    }

//----------------------------------------------------------------

/**
 * @brief Runs all prepared test cases
 *
 * @return TestPassed after all test cases have been executed
 *
 * @note Test cases are stored in an array of TestSquare structures
 *       Each test case is passed to the RunOneTest function
 */

int RunAllTest (void)
    {
        TestSquare testsAll[] = {   {.a = 1,  .b =  2,  .c =  1, .RootsRef = e_OneRoot, .x1Ref = -1},
                                    {.a = 1,  .b = -3,  .c =  2, .RootsRef = e_TwoRoot, .x1Ref =  2, .x2Ref =  1},
                                    {.a = 1,  .b =  0,  .c = -4, .RootsRef = e_TwoRoot, .x1Ref =  2, .x2Ref = -2},
                                    {.a = 1,  .b =  0,  .c =  1, .RootsRef = e_ZeroRoot},
                                    {.a = 1,  .b =  2,  .c =  5, .RootsRef = e_ZeroRoot},
                                    {.a = 2,  .b =  4,  .c =  2, .RootsRef = e_OneRoot, .x1Ref = -1},
                                    {.a = 2,  .b = -8,  .c =  8, .RootsRef = e_OneRoot, .x1Ref =  2},
                                    {.a = 1,  .b = -5,  .c =  6, .RootsRef = e_TwoRoot, .x1Ref =  3, .x2Ref =  2},
                                    {.a = 1,  .b =  1,  .c = -6, .RootsRef = e_TwoRoot, .x1Ref =  2, .x2Ref = -3},
                                    {.a = 1,  .b = -1,  .c = -2, .RootsRef = e_TwoRoot, .x1Ref =  2, .x2Ref = -1},
                                  };

        int size = sizeof(testsAll) / sizeof(TestSquare);
        for (int  i = 0; i < size; i++) RunOneTest (testsAll[i]);

        return 1;
    }

//----------------------------------------------------------------

/**
 * @brief Displays information about a failed test with one expected root
 *
 * @param [in] test Test case containing the expected root
 * @param [in] x1 First root received from the equation solver
 *
 * @note The function displays the expected and received values of the root
 */

void PrintTestFailOneRoot (TestSquare  test, float x1)
        {
            PrintfColor         ("Test Fail: The roots of the test and the solution did not match\n", RedColor);
            PrintfColorArgument ("Expected: x1 = %f\n", test.x1Ref, 0, 0,                             BlueColor);
            PrintfColorArgument ("Received: x1 = %f\n", x1,         0, 0,                             YellowColor);
        }

//----------------------------------------------------------------

/**
 * @brief Displays information about a failed test with two expected roots
 *
 * @param [in] test Test case containing the expected roots
 * @param [in] x1 First root received from the equation solver
 * @param [in] x2 Second root received from the equation solver
 * @param [in] Roots Number of roots received from the equation solver
 *
 * @note The function displays the expected and received number of roots and their values
 */

void PrintTestFailTwoRoot (TestSquare  test, float x1, float x2, int Roots)
    {
        PrintfColor         ("Test Fail: The roots of the test and the solution did not match\n",                    RedColor);
        PrintfColorArgument ("Expected: %d roots; x1 = %f; x2 = %f\n", (float)test.RootsRef, test.x1Ref, test.x2Ref, YellowColor);
        PrintfColorArgument ("Received: %d roots; x1 = %f; x2 = %f\n", (float)Roots,              x1,         x2,    BlueColor);
    }

//----------------------------------------------------------------

/**
 * @brief Calculates the 32-bit FNV-1a hash of a string
 *
 * @param [in] str String to be hashed
 * @param [in] len Length of the string in bytes
 *
 * @return 32-bit FNV-1a hash value
 *
 * @note The function is based on the FNV-1a hash implementation from Peter Scott's
 *       murmur3 repository example.c
 *
 * @see https://github.com/PeterScott/murmur3/blob/master/example.c
 */

uint32_t fnv32_hash(const char *str, size_t len)
    {
        const unsigned char *s = (const unsigned char *)str;

        const uint32_t FNV_32_PRIME = 0x01000193;

        uint32_t h = 0x811c9dc5;

        while (len--)
            {
                h ^= *s++;
                h *= FNV_32_PRIME;
            }

        return h;
    }

//----------------------------------------------------------------

/**
 * @brief Checks the user's login and password and displays the corresponding ASCII image
 *
 * @param [in] TextColor Color used to display authorization messages
 * @param [in] PictureColor Color used to display the ASCII image
 * @param [in] FileName Name of the file containing user login, password hash and photo file name
 *
 * @return true if the user enters correct login and password or chooses None
 * @return false if an error occurs while working with the authorization file
 *
 * @note The entered password is converted to an FNV-1a hash before comparison
 *
 * @note If the user enters None as the login, the authorization process is skipped
 *
 * @note If the user enters Registration as the login, the registration function is called
 *
 * @note If the login or password is incorrect, the user can try again
 *
 * @note After successful authorization, the ASCII image associated with the user is displayed
 */

bool CheckLoginPassword (int TextColor, int PictureColor, const char* FileName)
    {
        assert (FileName);

        while (Right)
        {
            char login[MaxLenLogin] = {};
            char password[MaxLenPassword] = {};

            PrintfColor ("Enter your login (Enter None to skip; to register, enter Registration): \n", TextColor);

            scanf ("%s", login);

            if (strcmp (login, "None") == 0) return Right;

            if (strcmp (login, "Registration") == 0)
                {
                    Registration (TextColor, FileName);

                    continue;
                }

            PrintfColor ("Enter your password: \n", TextColor);

            scanf ("%s", password);

            uint32_t passwordHash = fnv32_hash (password, strlen (password));

            FILE* File = fopen (FileName, "r");

            if (File == NULL)
                {
                    PrintfColor ("Input Error File\n", RedColor);

                    return Incorrect;
                }

            char fileLogin[MaxLenLogin] = {};
            uint32_t filePasswordHash = 0;
            char photoFileName[MaxPhotoFileName] = {};

            while (fscanf (File, "%s %u %s", fileLogin,&filePasswordHash, photoFileName) == 3)
                {
                    if (strcmp (login, fileLogin) == 0 && passwordHash == filePasswordHash)
                    {
                        fclose (File);

                        PrintASCII (photoFileName, PictureColor);

                        return Right;
                    }
                }

            fclose (File);

            PrintfColor ("Wrong login or password\n", RedColor);
        }

        return Incorrect;
    }

//----------------------------------------------------------------

/**
 * @brief Registers a new user and adds their data to the user database
 *
 * @param [in] TextColor Color used to display registration messages
 * @param [in] FileName Name of the file where the new user's data is stored
 *
 * @return true if the registration is completed successfully or cancelled by entering None
 * @return false if an error occurs while writing to the user database
 *
 * @note The function checks whether the entered username is already in use
 *
 * @note The entered password is converted to an FNV-1a hash before being saved
 *
 * @note The user must confirm the entered registration data before it is written to the file
 *
 * @note Entering No allows the user to enter the registration data again
 *
 * @note Entering None cancels the registration process
 *
 * @note User data is appended to the end of the database file without deleting existing users
 */


bool Registration (int TextColor, const char* FileName)
    {
        assert (FileName);

        while (Right)
        {
            char login[MaxLenLogin] = {};
            char password[MaxLenPassword] = {};
            char photoFileName[MaxPhotoFileName] = {};
            char answer[MaxLenAnswer] = {};

            PrintfColor ("Enter new login (Enter None to cancel registration): \n", TextColor);

            scanf ("%s", login);

            if (strcmp (login, "None") == 0) return Right;

            if (IsLoginExists (login, FileName) == Right)
                {
                    PrintfColor ("This username is busy, enter another one\n", RedColor);

                    continue;
                }

            PrintfColor ("Enter new password (Enter None to cancel registration): \n", TextColor);

            scanf ("%s", password);

            if (strcmp (password, "None") == 0) return Right;

            PrintfColor ("Enter photo file name (FileName.txt) (Enter None to cancel registration): \n", TextColor);

            scanf ("%s", photoFileName);

            if (strcmp (photoFileName, "None") == 0) return Right;

            while (Right)
            {
                PrintfColor ("Is the username and password entered correctly? (Yes/No, None to cancel): \n",
                             TextColor);

                scanf ("%s", answer);

                if (strcmp (answer, "Yes") == 0)
                    break;

                if (strcmp (answer, "No") == 0)
                    break;

                if (strcmp (answer, "None") == 0)
                    return Right;

                PrintfColor ("Please enter Yes or No\n", RedColor);
            }

            if (strcmp (answer, "No") == 0)
                continue;

            uint32_t passwordHash = fnv32_hash (password, strlen (password));

            FILE* File = fopen (FileName, "a");

            if (File == NULL)
                {
                    PrintfColor ("Input Error File\n", RedColor);

                    return Incorrect;
                }

            fprintf (File, "%s %u %s\n", login, passwordHash, photoFileName);

            fclose (File);

            PrintfColor ("Registration successful\n", GreenColor);

            return Right;
        }

        return Incorrect;
    }

//----------------------------------------------------------------

/**
 * @brief Checks whether a username already exists in the user database
 *
 * @param [in] Login Username to search for
 * @param [in] FileName Name of the file containing registered users
 *
 * @return true if the username already exists
 * @return false if the username was not found or the file could not be opened
 *
 * @note The function reads the user database without modifying its contents
 *
 * @note The function is used during registration to prevent duplicate usernames
 */

bool IsLoginExists (const char* Login, const char* FileName)
    {
        assert (Login);
        assert (FileName);

        FILE* File = fopen (FileName, "r");

        if (File == NULL) return Incorrect;

        char fileLogin[MaxLenLogin] = {};
        uint32_t filePasswordHash = 0;
        char photoFileName[MaxPhotoFileName] = {};

        while (fscanf (File, "%s %u %s", fileLogin, &filePasswordHash, photoFileName) == 3)
            {
                if (strcmp (Login, fileLogin) == 0)
                    {
                        fclose (File);

                        return Right;
                    }
            }

        fclose (File);

        return Incorrect;
    }

//----------------------------------------------------------------
