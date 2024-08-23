import ActiveElementCombination from "../components/combinations/activeElementCombination";
import Combination from "../components/combinations/combination";
import MinimumCombination from "../components/combinations/minimumCombination";
import PCGMain from "../components/pcgMain";

export default function CombinationGeneration() {
  return (
    <PCGMain>
      <h1>Combination Generation</h1>
      <Combination></Combination>
      <MinimumCombination></MinimumCombination>
      <ActiveElementCombination></ActiveElementCombination>
    </PCGMain>
  );
}
