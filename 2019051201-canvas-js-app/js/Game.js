import Timer from "./Timer.js";

const Game = (() => {
  const $gl = Symbol("gl");
  const $timer = Symbol("timer");

  const $tick = Symbol("tick");
  const $render = Symbol("render");

  return class {
    constructor(gl) {
      this[$gl] = gl;
      this[$timer] = new Timer();
    }

    start() {
      window.requestAnimationFrame(t => {
        this[$tick](t);
      });
    }

    [$tick](t) {
      this[$timer].tick(t);
      this[$render]();

      window.requestAnimationFrame(t => {
        this[$tick](t);
      });
    }

    [$render]() {
      const gl = this[$gl];
      const r = this[$timer].delta / 100;
      gl.clearColor(r, 0, 0, 1);
      gl.clear(gl.COLOR_BUFFER_BIT);
    }
  };
})();

export default Game;
