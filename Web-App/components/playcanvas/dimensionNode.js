import * as pc from "playcanvas";

export default function createDimensionNode() {
  var DimensionNode = pc.createScript("dimensionNode");

  DimensionNode.prototype.initialize = function () {
    this.dimension = 0;
    this.app.on(
      "SwitchDimension",
      (dimension) => (this.entity.enabled = dimension === this.dimension)
    );
  };
}
