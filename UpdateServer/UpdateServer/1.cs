using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UpdateServer
{
    public class One : IUpdate
    {
        public string version { get; private set; }

        public bool Run()
        {
            return true;
        }
    }
}
