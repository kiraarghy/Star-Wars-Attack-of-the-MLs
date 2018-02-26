type state = {
  personData: option(PersonData.person),
  count: int
};

type action =
  | Loaded(PersonData.person)
  | ClickIncrease
  | ClickDecrease;

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => ({personData: None, count: 1}: state),
  didMount: self => {
    let handlePersonLoaded = self.reduce(personData => Loaded(personData));
    PersonData.fetchPerson(
      "https://swapi.co/api/people/" ++ string_of_int(self.state.count) ++ "/"
    )
    |> Js.Promise.then_(personData => {
         handlePersonLoaded(personData);
         Js.Promise.resolve();
       })
    |> ignore;
    ReasonReact.NoUpdate;
  },
  reducer: (action, state) =>
    switch action {
    | Loaded(loadedPerson) =>
      ReasonReact.Update({
        ...state,
        personData: Some(loadedPerson),
        count: state.count
      })
    | ClickIncrease =>
      ReasonReact.Update({
        ...state,
        count:
          if (state.count < 88) {
            state.count + 1;
          } else {
            state.count;
          }
      })
    | ClickDecrease =>
      ReasonReact.Update({
        ...state,
        count:
          if (state.count > 1) {
            state.count - 1;
          } else {
            state.count;
          }
      })
    },
  render: self => {
    let personItem =
      switch self.state.personData {
      | Some(personData) => <PersonItem person=personData />
      | None => ReasonReact.stringToElement("Loading")
      };
    <div className="App">
      <h1
        style=(
          ReactDOMRe.Style.make(
            ~color="#FED02F",
            ~textAlign="center",
            ~fontSize="68px",
            ()
          )
        )>
        (ReasonReact.stringToElement("Star Wars Characters"))
      </h1>
      {personItem}
      <Button content="Increase" boop={_event => self.send(ClickIncrease)}/>
      <Button content="Decrease" boop={_event => self.send(ClickDecrease)}/>
    </div>;
  }
};