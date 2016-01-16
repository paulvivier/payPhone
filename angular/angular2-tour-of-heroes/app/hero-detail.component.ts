import {Component} from 'angular2/core';
import {Hero} from './hero';

@Component({
  selector: 'my-hero-detail',
  template: `
 	 <div *ngIf="hero" class="detail">
 	    <h2>{{hero.name}} details!</h2>
 	     <div>
		<label>id: </label>{{hero.id}}
	     </div>
 	     <div>
		<label>name: </label>
		<input [(ngModel)]="hero.name" placeholder="name"></div>
 	     </div>
 	      `,
  styles:[`
   .detail {
      position: fixed;
      right: 10;
      top: 10;
      background-color: lightgrey;
      padding: 5 20 20 20;
      font-family: monospace;
    }
`],

inputs: ['hero'],



})
export class HeroDetailComponent {
	public hero: Hero;

}
