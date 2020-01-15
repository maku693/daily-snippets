using UnityEngine;

namespace Inputs
{
    public class SwipeInput : MonoBehaviour
    {
        private static float cm2Inch = 0.3937008F;
        [SerializeField]
        private float minSwipeSpeed;
        private float minSwipeSpeedPixel => minSwipeSpeed * cm2Inch * Screen.dpi;

        [SerializeField]
        private float maxSwipeAngleSlip;
        private float maxSwipeAngleSlipTurn => maxSwipeAngleSlip / 360F;

        public bool GetSwipe(Vector2 angle)
        {
            if (Input.touchCount == 0) { return false; }

            var touch = Input.GetTouch(0);
            if (touch.phase != TouchPhase.Ended) { return false; }

            var swipeDelta = touch.deltaPosition;
            var minSwipeDelta = minSwipeSpeedPixel * touch.deltaTime;
            if (swipeDelta.magnitude < minSwipeDelta.magnitude) { return false; }

            var angleSlip = 1 - Vector2.Dot(angle, swipeDelta.normalized);
            if (angleSlip > maxSwipeAngleSlipTurn) { return false; }

            return true;
        }
    }
}
