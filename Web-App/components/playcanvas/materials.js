import * as pc from "playcanvas";

const colors = [pc.Color.RED, pc.Color.GREEN, pc.Color.BLUE, pc.Color.YELLOW];

export default function GetColor(index) {
  return colors[Math.abs(index) % colors.length];
}
