using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloWorldDeleteMe
{
    static class BreakEverything
    {
        unsafe static BreakEverything()
        {
            string str = "Hello World";

            fixed(char* c = str)
            {
                c[0] = 'n';
                c[1] = 'o';
                c[-2] = (char) 2;
            }
        }

        public static void Break() { }
    }
}
