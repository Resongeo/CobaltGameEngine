using Cobalt;

namespace Test
{
    public class Player : Entity
    {
        private float speed = 2f;

        void OnCreate()
        {
            Debug.Trace($"Player created");
        }

        void OnUpdate(float deltaTime)
        {
            Vector3 direction = new Vector3(0f);

            if(Input.GetKeyDown(KeyCodes.D))
            {
                direction.X = 1f;
            }
            else if (Input.GetKeyDown(KeyCodes.A))
            {
                direction.X = -1f;
            }
            if (Input.GetKeyDown(KeyCodes.W))
            {
                direction.Y = 1f;
            }
            else if (Input.GetKeyDown(KeyCodes.S))
            {
                direction.Y = -1f;
            }

            var normalized = Vector3.Normalize(direction);
            normalized.Z = 0f;
            normalized *= speed * deltaTime;
            Translate(normalized);
        }
    }
}
