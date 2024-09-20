import Link from "next/link";
import styles from "../styles/Home.module.css";

export default function PCGHeader() {
  return (
    <header className={styles.pcgHeader}>
      <Link href="/" className={styles.pcgHeaderLink}>
        Home
      </Link>
      <Link href="/simpleGeneration" className={styles.pcgHeaderLink}>
        Simple Generation
      </Link>
      <Link href="/multiDimensionGeneration" className={styles.pcgHeaderLink}>
        Multi Dimension Generation
      </Link>
      <Link
        href="/waveFunctionCollapseGeneration"
        className={styles.pcgHeaderLink}
      >
        Wave Function Collapse Generation
      </Link>
      <Link
        href="/waveFunctionCollapse4DGeneration"
        className={styles.pcgHeaderLink}
      >
        4D Wave Function Collapse Generation
      </Link>
      <Link
        href="/waveFunctionCollapseGrid2DGeneration"
        className={styles.pcgHeaderLink}
      >
        Grid 2D Wave Function Collapse Generation
      </Link>
      <Link
        href="/waveFunctionCollapseGrid3DGeneration"
        className={styles.pcgHeaderLink}
      >
        Grid 3D Wave Function Collapse Generation
      </Link>
      <Link href="/mazeGeneration" className={styles.pcgHeaderLink}>
        Maze Generation
      </Link>
      <Link href="/combinationGeneration" className={styles.pcgHeaderLink}>
        Combination Generation
      </Link>
      <Link href="/sequenceGeneration" className={styles.pcgHeaderLink}>
        Sequence Generation
      </Link>
      <Link href="/cyclicSequenceGeneration" className={styles.pcgHeaderLink}>
        Cyclic Sequence Generation
      </Link>
    </header>
  );
}
