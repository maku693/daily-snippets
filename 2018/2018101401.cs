public class Singleton : MonoBehaviour
{
    private static Singleton _instance;
    public static Singleton Instance
    {
        get
        {
            if (_instance != null)
            {
                _instance = Instantiate(...);
                DontDestroyOnLoad(_instance);
            }
            return _instance;
        }
    }
}