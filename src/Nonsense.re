type state = 
| Error 
| Words(list(string));

[@react.component]
let make = _ => {
  let (state, setState) = React.useState(_ => Words([]));
  
  let decodeWords = (json: Js.Json.t) : list(string) => 
    switch(Js.Json.decodeArray(json)) {
      | None => []
      | Some(array) => Belt.Array.reduce(array, [], (acc, value) => {
        switch(Js.Json.decodeString(value)) {
          | None => acc
          | Some(v) => [v, ...acc]
        }
      })
    };

  let gotWords = (words': list(string)) : unit => 
    setState(state => 
      switch(state){
        | Error => Error
        | Words(words) => Words(List.append(words, words'))
      });

  React.useEffect0( () => {
      Fetch.fetch("https://random-word-api.herokuapp.com/word?number=20")
      |> Js.Promise.then_(Fetch.Response.json)
      |> Js.Promise.then_(json => {
          gotWords(decodeWords(json));
          Js.Promise.resolve();
        })
      |> ignore;
    None;
  });
  <div>
    {switch(state) {
      | Error => React.string("Application is in error!")
      | Words([]) => React.string("loading....")
      | Words(words) => <ul> {Belt.List.toArray(Belt.List.mapWithIndex(words, (i, word) => <li key={Belt.Int.toString(i)}>{React.string(word)}</li>)) -> React.array} </ul>
    }}
  </div>;
};