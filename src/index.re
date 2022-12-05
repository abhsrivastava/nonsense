Js.log("Hello World1");
switch (ReactDOM.querySelector("#nonsense")) {
| Some(nonsense) => ReactDOM.render(<Nonsense />, nonsense)
| None => Js.log("we could not find nonsense div!"); ()
};