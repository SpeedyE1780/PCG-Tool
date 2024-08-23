import * as pc from "playcanvas";

export default function createDestroyNode() {
  var DestroyNode = pc.createScript("destroyNode");

  DestroyNode.prototype.initialize = function () {
    this.app.on("DestroyNode", () => this.entity.destroy());
  };
}
