namespace Cobalt
{
    public class Input
    {
        public static bool GetKeyDown(KeyCodes key)
        {
            return InternalCalls.Input_GetKeyDown((int)key);
        }
    }
}
