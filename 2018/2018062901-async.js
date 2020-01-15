const f = async () => (42);
(async () => {
  console.log(await f());
})();
