import { useEffect } from "react";
import * as pc from "playcanvas";
import CreateFLyCamera from "./flyCamera";

export default function Game() {
  useEffect(() => {
    // create a PlayCanvas application
    const canvas = document.getElementById("application");
    const app = new pc.Application(canvas, {
      mouse: new pc.Mouse(document.body),
      keyboard: new pc.Keyboard(window),
    });
    app.setCanvasResolution(pc.RESOLUTION_AUTO);
    app.setCanvasFillMode(pc.FILLMODE_FILL_WINDOW);
    app.start();

    CreateFLyCamera();

    // create a camera
    const camera = new pc.Entity();
    camera.addComponent("camera", {
      clearColor: new pc.Color(0.3, 0.3, 0.7),
    });
    camera.addComponent("script");
    camera.script.create("flyCamera");
    camera.setPosition(0, 0, 3);
    app.root.addChild(camera);

    // create a light
    const light = new pc.Entity();
    light.addComponent("light");
    light.setEulerAngles(45, 45, 0);
    app.root.addChild(light);

    // create a box
    const box = new pc.Entity();
    box.addComponent("model", {
      type: "box",
    });

    var Rotate = pc.createScript("rotate");
    Rotate.prototype.update = function (dt) {
      this.entity.rotate(10 * dt, 20 * dt, 30 * dt);
    };

    box.addComponent("script");
    box.script.create("rotate");
    app.root.addChild(box);
  }, []);

  return <canvas id="application"></canvas>;
}
