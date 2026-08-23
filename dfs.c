void OutputValues (int res, float x1, float x2, int TextColor, int AnswerColor)
    {
        switch(Roots)
            {
                case e_ZeroRoot: PrintfColor            ("There are no solutions\n",                           TextColor);
                                 return        TestFailed;
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

// =======================================================================================================================================================


bool RunOneTest (TestSquare  test) // TODO
    {
        float x1 = 0, x2 = 0;
        RootNumber Roots = SolvingEquation (test.a, test.b, test.c, &x1, &x2);

                       PrintfColorTreeArgument("%fx^2 + %fx + %f = 0\n",                 test.a,        test.b,     test.c,     LightMagentaColor);
                       PrintfColorTreeArgument("Test Fail: a = %f, b = %f, c = %f\n",    test.a,        test.b,     test.c,     RedColor);
                       PrintfColorTreeArgument("Expected: %d roots; x1 = %f; x2 = %f\n", test.RootsRef, test.x1Ref, test.x2Ref, YellowColor);
                       PrintfColorTreeArgument("Received: %d roots; x1 = %f; x2 = %f\n", Roots,         x1,         x2,         BlueColor);

        if (Roots != test.RootsRef)
            {
                       PrintfColorTreeArgument("%fx^2 + %fx + %f = 0\n",                 test.a,        test.b,     test.c,     LightMagentaColor);
                       PrintfColorTreeArgument("Test Fail: a = %f, b = %f, c = %f\n",    test.a,        test.b,     test.c,     RedColor);
                       PrintfColorTreeArgument("Expected: %d roots; x1 = %f; x2 = %f\n", test.RootsRef, test.x1Ref, test.x2Ref, YellowColor);
                       PrintfColorTreeArgument("Received: %d roots; x1 = %f; x2 = %f\n", Roots,         x1,         x2,         BlueColor);

                return        TestFailed;
            }
        else if (Roots == e_OneRoot)
            {
                if ((CompFloat(x1, test.x1Ref) != e_AreEqual)) // TODO
                    {
                        PrintfColorTreeArgument("%fx^2 + %fx + %f = 0\n",                 test.a,        test.b,     test.c,     LightMagentaColor);
                        PrintfColorTreeArgument("Test Fail: a = %f, b = %f, c = %f\n",    test.a,        test.b,     test.c,     RedColor);
                        PrintfColorTreeArgument("Expected: %d roots; x1 = %f; x2 = %f\n", test.RootsRef, test.x1Ref, test.x2Ref, YellowColor);
                        PrintfColorTreeArgument("Received: %d roots; x1 = %f; x2 = %f\n", Roots,         x1,         x2,         BlueColor);

                        return TestFailed;
                    }
            }
        else if (Roots == e_TwoRoot)
            {
                if ((CompFloat(x1, test.x1Ref) != e_AreEqual) || (CompFloat(x2, test.x2Ref) != e_AreEqual))
                    {
                        PrintfColorTreeArgument("%fx^2 + %fx + %f = 0\n",                 test.a,        test.b,     test.c,     LightMagentaColor);
                        PrintfColorTreeArgument("Test Fail: a = %f, b = %f, c = %f\n",    test.a,        test.b,     test.c,     RedColor);
                        PrintfColorTreeArgument("Expected: %d roots; x1 = %f; x2 = %f\n", test.RootsRef, test.x1Ref, test.x2Ref, YellowColor);
                        PrintfColorTreeArgument("Received: %d roots; x1 = %f; x2 = %f\n", Roots,         x1,         x2,         BlueColor);

                        return TestFailed;
                    }
            }

        PrintfColor ("APPROVED\n", GreenColor);

        return TestPassed;
    }
