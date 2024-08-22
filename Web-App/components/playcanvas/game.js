import { useEffect } from "react";
import * as pc from "playcanvas";
import CreateFlyCamera from "./flyCamera";
import SpawnMazeNode from "../maze/spawnMazeNode";

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

    CreateFlyCamera();

    // create a camera
    const camera = new pc.Entity();
    camera.addComponent("camera", {
      clearColor: new pc.Color(0.3, 0.3, 0.7),
    });
    camera.addComponent("script");
    camera.script.create("flyCamera");
    camera.setPosition(0, 5, 5);
    camera.lookAt(0, 0, 0);
    app.root.addChild(camera);

    // create a light
    const light = new pc.Entity();
    light.addComponent("light");
    light.setEulerAngles(45, 45, 0);
    app.root.addChild(light);

    SpawnMazeNode(3);
  }, []);

  return <canvas id="application"></canvas>;
}
