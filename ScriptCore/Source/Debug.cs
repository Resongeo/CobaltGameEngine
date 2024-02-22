namespace Cobalt
{
    public class Debug
    {
        public static void Trace(string message) => InternalCalls.EngineLog_Trace(message);
        public static void Info(string message) => InternalCalls.EngineLog_Info(message);
        public static void Warn(string message) => InternalCalls.EngineLog_Warn(message);
        public static void Error(string message) => InternalCalls.EngineLog_Error(message);
    }
}
