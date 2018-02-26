let component = ReasonReact.statelessComponent("ButtonView");
let make = (~content, ~boop, _children) => {
...component,
  render: _self =>
      <button
        className="decreaseNumber"
        onClick={boop}
        style=(
          ReactDOMRe.Style.make(
            ~color="#FED02F",
            ~textAlign="center",
            ~fontSize="68px",
            ()
          )
        )>
        (ReasonReact.stringToElement("Click me to" ++ content))
      </button>
};