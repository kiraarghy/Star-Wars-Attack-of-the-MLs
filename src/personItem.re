let component = ReasonReact.statelessComponent("PersonItem");

let style = ReactDOMRe.Style.make(~color="white", ~fontSize="20px", ());

let make = (~person: PersonData.person, _children) => {
  ...component,
  render: _self =>
    <div>
      <div className="person__name" style>
        (ReasonReact.stringToElement("Name : " ++ person.name))
      </div>
      <div className="person__height" style>
        (ReasonReact.stringToElement("Height : " ++  person.height))
      </div>
    </div>
};