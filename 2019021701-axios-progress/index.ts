import axios from "axios";
import { Observable, Subject } from "rxjs";

export class Response<T> {
  private _progress: number;
  public get progress() {
    return this._progress;
  }

  private _data: T | undefined;
  public get data() {
    return this._data;
  }

  public get isLoading() {
    return this._data ? false : true;
  }

  public constructor(progress = 0, data: T | undefined = undefined) {
    this._progress = progress;
    this._data = data;
  }
}

interface GetUUIDResponse {
  uuid: string;
}

export const getUUID = () => {
  const subject = new Subject<Response<GetUUIDResponse>>();
  (async () => {
    const response = await axios.get<GetUUIDResponse>(
      "https://httpbin.org/uuid",
      {
        onDownloadProgress: (e: ProgressEvent) => {
          subject.next(new Response(e.total / e.loaded));
        }
      }
    );
    subject.next(new Response<GetUUIDResponse>(1, response.data));
  })();
  return subject as Observable<Response<GetUUIDResponse>>;
};
