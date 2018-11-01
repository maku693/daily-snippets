const canvas = document.createElement("canvas");
const ctx = canvas.getContext("2d");

const text = "TEXT";

ctx.font = "16px";
const { width: textWidth } = ctx.measureText(text);

canvas.width = textWidth;
canvas.height = 16 * 1.2;
ctx.fillText(text, 0, 16 * 1.2);
