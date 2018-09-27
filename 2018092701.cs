using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

[CreateAssetMenu]
public class LoopAudioParams : ScriptableObject
{
    public AudioClip audioClip;
    public List<float> timePoints;
}
