using UnityEngine;
using UnityEngine.EventSystems;

public class PaperRoll : MonoBehaviour
{
    private bool isPulled;
    private float pullSpeed;

    public void OnEndDrag(PointerEventData eventData)
    {
        if (isPulled) { return; }
        isPulled = true;

        var pullDistance = (eventData.position - eventData.pressPosition).magnitude;
        var pullDistanceInCm = pullDistance / Screen.dpi * inch2cm;
        var pullDuration = Time.time - eventData.clickTime;
        pullSpeed = pullDistanceInCm / pullDuration;
    }
}
