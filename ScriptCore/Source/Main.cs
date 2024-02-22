using System;

namespace Cobalt
{
    public class Main
    {
        public Main()
        {
            for(int i = 0; i < 10; i++)
            {
                Debug.Error($"Engine ERROR log from C#. Count: {i + 1}");
            }
        }
    }
}