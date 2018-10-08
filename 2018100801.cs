using System.Collections.Generic;
using UnityEngine;

namespace UIs.Common
{
    public class FadeInOut : MonoBehaviour
    {
        [SerializeField]
        private Animator animator;

        private void Start()
        {
            animator.SetTrigger("FadeIn");
        }
    }
}
