[@bs.val] [@bs.return nullable] [@bs.scope "document"]
external getElementById: string => option(Dom.element) = "getElementById";

type t;

type mount = {
  id: string,
  node: React.element,
};

module TestComponent = {
  [@react.component]
  let make = () => "React TestComponent"->React.string;
};

let mounts = [|{id: "react-mount-test", node: <TestComponent />}|];

ReactDOMRe._getElementsByClassName;

type classMounts =
  | AddRemoveSuggestedVendorsButton;

let elementsById = {
  Array.map(
    mount =>
      switch (getElementById(mount.id)) {
      | None => React.null
      | Some(el) => ReactDOMRe.createPortal(mount.node, el)
      },
    mounts,
  )
  ->React.array;
};

ReactDOMRe.renderToElementWithId(
  <div> elementsById </div>,
  "react-mount-main",
);
