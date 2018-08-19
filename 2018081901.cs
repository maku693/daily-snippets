using System;
using UnityEngine;

namespace Games
{
    public class Pigeon : MonoBehaviour
    {
        [SerializeField]
        private Rigidbody rb;

        private void Update()
        {
            var pos = rb.transform.position;
            pos.x += 0.01F;
            rb.transform.position = pos;
        }
    }
}
