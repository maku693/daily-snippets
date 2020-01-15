const cancellable = original => {
  let triggerCancel;
  const cancel = () => triggerCancel();
  const cancelPromise = new Promise(resolve => {
    triggerCancel = resolve;
  });
  const promise = Promise.race([original, cancelPromise]);
  promise.cancel = cancel;
  return promise;
};

const promise = cancellable(new Promise(resolve => setTimeout(resolve, 1000)));
promise.then(() => { console.log("resolve"); });
setTimeout(promise.cancel, 10);
