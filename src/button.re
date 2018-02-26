let component = ReasonReact.statelessComponent("ButtonView");
let make = (~content, ~boop, _children) => {
...component,
  render: _self =>
      <button
        className="decreaseNumber"
        onClick={boop}
        style=(
          ReactDOMRe.Style.make(
            ~color="grey",
            ~textAlign="center",
            ~fontSize="20px",
            ~border="2px solid darkGrey",
            ()
          )
        )>
        (ReasonReact.stringToElement(content))
      </button>
};