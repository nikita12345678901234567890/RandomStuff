using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UpdateServer
{
    public interface IUpdate
    {
        public string version { get; }

        public bool Run();
    }
}
