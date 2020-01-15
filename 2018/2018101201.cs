using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Playables;
using UniRx;

namespace UIs.Common
{
    public class FadeInOut : MonoBehaviour
    {
        [SerializeField]
        private Animator animator;

        private ISubject<Unit> _showAnimatonEnd = new Subject<Unit>();
        public IObservable<Unit> OnShowAnimationEndAsObservable => _showAnimatonEnd;

        public void BeginShowAnimation()
        {
            animator.SetBool("IsVisible", true);
        }

        public void OnShowAnimationEnd()
        {
            _showAnimatonEnd.OnNext(Unit.Default);
        }
    }
}
