const Timer = (() => {
  return class {
    constructor() {
      this.now = this.lastTicked = 0;
    }
    get delta() {
      return this.now - this.lastTicked;
    }
    tick(now) {
      this.lastTicked = this.now;
      this.now = now;
    }
  };
})();

export default Timer;
