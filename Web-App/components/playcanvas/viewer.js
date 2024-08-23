import Game from "./game";
import styles from "../../styles/Home.module.css";

export default function Viewer({ children }) {
  return (
    <div className={styles.viewer}>
      {children}
      <Game></Game>
    </div>
  );
}
