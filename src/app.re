type state = {
  personData: option(PersonData.person),
  count: int
};

type action =
  | Loaded(PersonData.person)
  | ClickIncrease
  | ClickDecrease
  | ClickReset;

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
        personData: Some(loadedPerson)
      })
    | ClickIncrease =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          count:
            if (state.count < 88) {
              state.count + 1;
            } else {
              state.count;
            }
        },
        (
          self => {
            let loadPerson = self.reduce(personData => Loaded(personData));
            PersonData.fetchPerson(
              "https://swapi.co/api/people/"
              ++ string_of_int(state.count)
              ++ "/"
            )
            |> Js.Promise.then_(personData => {
                 loadPerson(personData);
                 Js.Promise.resolve();
               })
            |> ignore;
          }
        )
      )
    | ClickDecrease =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          count:
            if (state.count > 1) {
              state.count - 1;
            } else {
              state.count;
            }
        },
        (
          self => {
            let loadPerson = self.reduce(personData => Loaded(personData));
            PersonData.fetchPerson(
              "https://swapi.co/api/people/"
              ++ string_of_int(state.count)
              ++ "/"
            )
            |> Js.Promise.then_(personData => {
                 loadPerson(personData);
                 Js.Promise.resolve();
               })
            |> ignore;
          }
        )
      )
      |ClickReset =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          count: 1
        },
        (
          self => {
            let loadPerson = self.reduce(personData => Loaded(personData));
            PersonData.fetchPerson(
              "https://swapi.co/api/people/"
              ++ string_of_int(state.count)
              ++ "/"
            )
            |> Js.Promise.then_(personData => {
                 loadPerson(personData);
                 Js.Promise.resolve();
               })
            |> ignore;
          }
        )
      ) 
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
      personItem
      <Button content="Click for next character" boop=(_event => self.send(ClickIncrease)) />
      <p/>
      <Button content="Click for previous character" boop=(_event => self.send(ClickDecrease)) />
      <p/>
      <Button content="Click to reset" boop=(_event => self.send(ClickReset)) />
    </div>;
  }
};