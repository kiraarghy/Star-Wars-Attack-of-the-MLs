type person = {
  name: string,
  height: string
};

let parsePersonJson = (json: Js.Json.t) : person => {
  name: Json.Decode.field("name", Json.Decode.string, json),
  height: Json.Decode.field("height", Json.Decode.string, json)
};
let fetchPerson = (personUrl) =>

  Fetch.fetch(personUrl)
  |> Js.Promise.then_(Fetch.Response.text)
  |> Js.Promise.then_(jsonText =>
       Js.Promise.resolve(parsePersonJson(Js.Json.parseExn(jsonText)))
     );

