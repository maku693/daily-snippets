export interface State {
  readonly title: string;
}

export function updateDocumentTitle(title: string) {
  let newTitle: string;
  if (document !== undefined) {
    document.title = title;
    newTitle = document.title;
  } else {
    newTitle = title;
  }
  return {
    title: newTitle,
    type: "UPDATE_DOCUMENT_TITLE"
  };
}

export type Action = ReturnType<typeof updateDocumentTitle>;

export default function(state: State, action: Action) {
  switch (action.type) {
    case "UPDATE_DOCUMENT_TITLE":
      return {
        title: action.title,
        ...state
      };
    default:
      return state;
  }
}
