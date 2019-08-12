import Game from "./Game.js";

const canvas = document.createElement("canvas");
document.body.appendChild(canvas);

window.addEventListener(
  "resize",
  () => {
    const r = canvas.getBoundingClientRect();
    canvas.width = r.width;
    canvas.height = r.height;
  },
  { passive: true }
);

const game = new Game(canvas.getContext("webgl"));
game.start();
