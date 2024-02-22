namespace Cobalt
{
    public class Entity
    {
        private ulong UUID = 0;

        protected Entity() { UUID = 0; }
        internal Entity(ulong uuid)
        {
            UUID = uuid;
        }

        public void Translate(Vector3 translation)
        {
            InternalCalls.Transform_Translate(UUID, translation);
        }
    }
}
