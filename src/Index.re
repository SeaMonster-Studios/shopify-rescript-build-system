type element;
[@bs.val] [@bs.return nullable] [@bs.scope "document"]
external getElementById: string => option(element) = "getElementById";

type mount = {
  id: string,
  node: React.element,
};

module Mount1 = {
  [@react.component]
  let make = () =>
    <h1> {React.string("Mount 1: I come from the land of Reason")} </h1>;
};

module Mount2 = {
  [@react.component]
  let make = () =>
    <h1> {React.string("Mount 2: I come from the land of Reason")} </h1>;
};

let mounts = [|
  {id: "react-mount-1", node: <Mount1 />},
  {id: "react-mount-2", node: <Mount2 />},
|];

Array.map(
  mount =>
    switch (getElementById(mount.id)) {
    | None => ()
    | Some(_el) => ReactDOMRe.renderToElementWithId(mount.node, mount.id)
    },
  mounts,
);